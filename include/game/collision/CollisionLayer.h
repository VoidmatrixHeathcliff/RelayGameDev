#pragma once

using layer_t = size_t;

namespace CollisionLayer {
	inline constexpr layer_t NoneLayer = 0;
	inline constexpr layer_t EnemyLayer = 1 << 0;
	inline constexpr layer_t PlayerLayer = 1 << 1;
	inline constexpr layer_t BlockLayer = 1 << 2;
}

enum class HitboxType :int {
	Static,
	Dynamic
};