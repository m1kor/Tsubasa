#include <Tsubasa/Core/Assets/AssetRegistry.h>

namespace Tsubasa
{
    void AssetRegistry::AddAssetSource(std::unique_ptr<AssetSource> source)
    {
        assetSources.push_back(std::move(source));
    }
}
