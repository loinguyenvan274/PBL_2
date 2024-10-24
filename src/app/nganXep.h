#ifndef _NGANXEP
#define _NGANXEP

#include "quanLy.h"
class giaoDien;

template <typename S>
class NganXep
{
private:
    QuanLy<S> mang;

public:
    void dayLen(const S &phanTu)
    {
        mang.them(phanTu);
    }

    void xoaDinh()
    {
        if (!rong())
        {
            mang.xoa(mang.lDCCuoi());
        }
        else
        {
            throw std::runtime_error("ngan xep rong");
        }
    }

    const S &layDinh() const
    {
        if (!rong())
        {
            return *(mang.lDCCuoi());
        }
        else
        {
            throw std::runtime_error("Ngan xep rong");
        }
    }

    bool rong() const
    {
        return mang.lSoPhanTu() == 0;
    }

    size_t kichThuoc() const
    {
        return mang.lSoPhanTu();
    }
};

#endif // _NGANXEP
