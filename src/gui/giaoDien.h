#ifndef _GIAODIEN
#define _GIAODIEN
#include "hopChu.h"
#include "bang.h"

#include "../app/Vector.h"
#include "../app/Nguoi.h"
#include "../app/SinhVien.h"
#include "../app/Phong.h"
#include "../app/docGhiFile.h"
#include "../app/QuanLyKTX.h"

#define MAU_XANH {65, 105, 225, 255}
#define MAU_LA_CAY {0, 128, 128, 255}
#define MAU_DEN_MO {255, 255, 255, 80}

struct NutTuyChon
{
    Vector<hopChu> dSNut;
    int nutBiRangBuot;
    void bieuDien();
    void capNhatTT();
    NutTuyChon();
};
enum NgonNgu
{
    TIENG_VIET,
    TIENG_ANH,
    TIENG_NHAT

};
enum ChuDeGiaoDien
{
    GD_SANG,
    GD_TOI
};
struct HeThong
{
    unsigned int bacGiaDien[6];
    unsigned long giaDien[6];
    unsigned long giaNuoc;
    string tenDonVi;
    string diaChi;
    unsigned long giaPhongMatDinh;
    unsigned long giaCocMatDinh;
    NgonNgu ngonNgu;
    ChuDeGiaoDien chuDeGD;
};

class giaoDien
{
protected:
    // bool flagNhap;

    QuanLyKTX &quanLyKTX;

    int soSinhVien, soPhong;

    Bang *table;
    hopChu boxThem, boxXoa, boxTimKiem;
    int sohangBD;
    bool flagTimKiem;                                             // dùng để tìm kiếm
    string chuoiTimSoSanh;
    HeThong *heThong;                                             // dung để kiểm tra cập nhật tìm kiếm nếu chuổi vừa mới nhật khác chuổi vừa nảy thì sẽ tìm kiếm lại
    const string floatSangString(const float &, const int & = 4); // loai bỏ số 000 dư thừa phía sau;
    const float stringSangFloat(const string &);

public:
    static Font font26;
    giaoDien(QuanLyKTX &, HeThong&);
    virtual void capNhatTT() = 0;
    virtual void bieuDien() = 0;
    virtual ~giaoDien() = default;
};

#endif