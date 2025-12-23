#include <algorithm> // For min, max (though not strictly needed for these formulas)
#include <cmath>     // For sqrt, ceil, floor
#include <iostream>

// 为了方便，使用 long long 类型，因为 n 和 m 可以很大
using ll = long long;

int main() {
    // 禁用 C++ 标准流与 C 标准流同步，加速输入输出
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T; // 测试用例的数量
    std::cin >> T;
    while (T--) {
        ll n, m; // n: AI数量, m: 冲突对数
        std::cin >> n >> m;

        ll best_case_max_is;  // 最好情况下的最大独立集大小
        ll worst_case_max_is; // 最坏情况下的最大独立集大小

        // --- 计算最好情况（最大独立集的最大值） ---
        if (m == 0) {
            // 如果没有冲突，所有AI都可以一起玩
            best_case_max_is = n;
        } else {
            // 找到最小的 k_best，使得 k_best * (k_best - 1) / 2 >= m
            // k_best 表示至少需要多少个节点才能承载 m 条边（形成一个团）
            // k_best = ceil((1 + sqrt(1 + 8m)) / 2)
            // 使用 long double 来保证 sqrt 计算的精度，然后进行 ceil
            ll k_best = static_cast<ll>(std::ceil((1.0 + std::sqrt(1.0 + 8.0 * m)) / 2.0));

            // 最好情况：用 k_best 个节点承载 m 条边，使其形成一个子图 (例如K_k_best)，
            // 且该子图的最大独立集为1。
            // 剩余 n - k_best 个节点是孤立的，都可以加入独立集。
            // 所以总大小为 (n - k_best) + 1。
            best_case_max_is = n - k_best + 1;
        }

        // --- 计算最坏情况（最大独立集的最小值） ---
        // 找到最大的 k_worst，使得 k_worst * (k_worst - 1) / 2 <= m
        // k_worst 表示我们可以用 m 条边形成的最大团的节点数
        // k_worst = floor((1 + sqrt(1 + 8m)) / 2)
        ll k_worst = static_cast<ll>(std::floor((1.0 + std::sqrt(1.0 + 8.0 * m)) / 2.0));

        // 剩余的边数
        ll m_rem = m - k_worst * (k_worst - 1) / 2;

        // 最坏情况：形成一个 K_k_worst 团，其最大独立集为1。
        // 剩余 n - k_worst 个节点，我们用 m_rem 条边，把它们中的 m_rem 个连接到 K_k_worst 中的一个节点。
        // 这样，这 m_rem 个节点也不能和 K_k_worst 中选出的唯一节点同时存在。
        // 所以，K_k_worst 提供 1 个节点。
        // 剩下的 n - k_worst - m_rem 个节点是孤立的，可以全部加入独立集。
        // 总大小为 1 + (n - k_worst - m_rem)。
        worst_case_max_is = 1 + (n - k_worst - m_rem);

        // 输出结果
        std::cout << best_case_max_is << " " << worst_case_max_is << "\n";
    }

    return 0;
}
