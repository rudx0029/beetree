//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include <vector>

namespace bte {
namespace test {

class Fibonochi
{
public:
    Fibonochi(int start = 0)
    {
        m_x[0] = start;
        m_x[1] = start;
    }

    std::vector<int> produce(int len)
    {
        std::vector<int> f;
        f.push_back(1);
        f.push_back(1);
        for (int i = 0; i < len - 2; i++)
        {
            int n_1 = f[f.size() - 2];
            int n   = f[f.size() - 1];
            f.push_back(n + n_1);
        }
        return std::move(f);
    }

    int next()
    {
        int res = 0;
        if (m_x[0] == 0)
        {
            res    = 1;
            m_x[0] = 1;
            m_x[1] = 1;
        }
        else
        {
            res    = m_x[0] + m_x[1];
            m_x[1] = m_x[0];
            m_x[0] = res;
        }

        return res;
    }

private:
    int m_x[2] = {0};
};

}  // namespace test
}  // namespace bte