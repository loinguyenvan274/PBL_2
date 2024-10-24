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
            throw std::runtime_error("Ngăn xếp rỗng, không thể xóa.");
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
            throw std::runtime_error("Ngăn xếp rỗng, không có phần tử ở đỉnh.");
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
