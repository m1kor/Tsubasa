#pragma once

#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <Tsubasa/Assets/AssetSource.h>

namespace Tsubasa
{
    class AssetRegistry : public std::enable_shared_from_this<AssetRegistry>
    {
    private:
        std::vector<std::unique_ptr<AssetSource>> assetSources;
        std::unordered_map<std::type_index,
                           std::unordered_map<std::string, std::weak_ptr<void>>>
            resources;
        std::mutex resources_mutex; // For thread safety

        template <typename T>
        static void AppendToKey(std::ostringstream &oss, const T &value)
        {
            oss << "#" << value;
        }

        template <typename... Args>
        static std::string MakeCacheKey(const std::string &path, const Args &...args)
        {
            std::ostringstream oss;
            oss << path;
            (AppendToKey(oss, args), ...);
            return oss.str();
        }

    public:
        AssetRegistry() = default;
        ~AssetRegistry() = default;


        void AddAssetSource(std::unique_ptr<AssetSource> source);

        template <typename T, typename... Args>
        std::shared_ptr<T> Load(const std::string &path, Args &&...args)
        {
            std::lock_guard<std::mutex> lock(resources_mutex);

            auto type_key = std::type_index(typeid(T));
            auto &type_map = resources[type_key];

            std::string cache_key = MakeCacheKey(path, args...);

            // Check if already loaded and still alive
            auto it = type_map.find(cache_key);
            if (it != type_map.end())
            {
                if (auto existing = it->second.lock())
                {
                    return std::static_pointer_cast<T>(existing);
                }
            }

            // Load with asset sources
            if (assetSources.empty())
            {
                throw std::runtime_error("No asset sources available");
            }
            std::vector<uint8_t> data;
            for (const auto &source : assetSources)
            {
                if (source->Exists(path))
                {
                    data = source->ReadBinary(path);
                    break;
                }
            }
            if (data.empty())
            {
                throw std::runtime_error("Asset not found: " + path);
            }

            // Create resource with custom deleter
            auto registry_weak = weak_from_this();
            auto resource = std::shared_ptr<T>(
                new T(path, data, std::forward<Args>(args)...),
                [registry_weak, type_key, cache_key](T *ptr)
                {
                    if (auto registry = registry_weak.lock())
                    {
                        std::lock_guard<std::mutex> lock(registry->resources_mutex);
                        auto type_it = registry->resources.find(type_key);
                        if (type_it != registry->resources.end())
                        {
                            type_it->second.erase(cache_key);
                            if (type_it->second.empty())
                            {
                                registry->resources.erase(type_it);
                            }
                        }
                    }
                    delete ptr;
                });

            type_map[cache_key] = resource;
            return resource;
        }

        template <typename T, typename... Args>
        std::shared_ptr<T> Get(const std::string &path, const Args &...args)
        {
            std::lock_guard<std::mutex> lock(resources_mutex);

            auto type_key = std::type_index(typeid(T));
            auto type_it = resources.find(type_key);
            if (type_it == resources.end())
                return nullptr;

            std::string cache_key = MakeCacheKey(path, args...);

            auto it = type_it->second.find(cache_key);
            if (it == type_it->second.end())
                return nullptr;

            return std::static_pointer_cast<T>(it->second.lock());
        }
    };
}
