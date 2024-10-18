#ifndef _COBAN
#define _COBAN

#define KHONG_TIM_THAY 0xffffffffffffffffull
typedef unsigned long long size_t;

struct thoiGianNTN
{
    int ngay;
    int thang;
    int nam;
};
struct thoiGianGPG
{
    int gio;
    int phut;
    int giay;
};
// coban.h
template <typename T>
class Vector
{
private:
    size_t doLon;
    size_t soPhanTu;
    T *conTro;
    void keoLui(const size_t &);
    void dayToi(const size_t &);
    void doi(T &, T &);
    void capPhat();

public:
    Vector(const size_t & = 0);
    Vector(const size_t &, const T &);
    T &operator[](size_t) const;
    T *viTriDau() const;
    T *viTriCuoi() const;

    size_t lDoLon() const;
    size_t lSoPhanTu() const;

    size_t tim(const T &) const;
    void xoa(const T &);
    void chen(const size_t &, const T &);
    ~Vector();
};
// conban.cpp

/*
khai bao cacs thanh vien khi kho taoj
cos ham add la add vaof cuoios cungf
có hàm xóa là xóa vào vị trí cuối cùng giải phóng bộ nhớ
lay phan tu -> da nang hoa toan tu truoc


*/
#endif