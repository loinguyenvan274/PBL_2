#include "giaoDienPhong.h"

giaoDienPhong ::giaoDienPhong(quanLyGiaoDien &qLGiaoDienDV)
{

    qLGiaoDien = &qLGiaoDienDV;

    font28 = LoadFontEx("assets/roboto.ttf", 26, const_cast<int *>(vietnameseCodepoints), sizeof(vietnameseCodepoints) / sizeof(int));

    // table ;

    int soDongToiDA = 1000;
    viTriLuu = new int[soDongToiDA]; // dùng để tìm kiếm
    flagTimKiem = false;

    table = new Bang({10, 200}, 8, soDongToiDA, {250, 36});
    table->cTieuDe(true);
    table->cDangHangCot(3, 0);
    table->cKieuChu(font28, 26);
    table->cGioHanBD(table->lViTri().y, GetScreenHeight());

    (*table)(0, 0).cNoiDung("STT");
    (*table)(0, 1).cNoiDung("Họ và tên");
    (*table)(0, 2).cNoiDung("Ngày sinh");
    (*table)(0, 3).cNoiDung("MSV");
    (*table)(0, 4).cNoiDung("Ngày ở");
    (*table)(0, 5).cNoiDung("Số Tháng");
    (*table)(0, 6).cNoiDung("Mã phòng");
    (*table)(0, 7).cNoiDung("Xóa");

    table->cCot(0, 60);
    table->cCot(1, 280);
    table->cCot(2, 250);
    table->cCot(3, 200);
    table->cCot(4, 210);
    table->cCot(5, 160);
    table->cCot(6, 240);
    table->cCot(7, 60);
    capNhatThuTu();
    // hộp xóa
    boxThemSinhVien = new hopChu({1030, 134, 210, 40}, "   Thêm sinh viên", BLUE, YELLOW, BLACK);
    (*boxThemSinhVien).cKieuChu(font28);
    (*boxThemSinhVien).cCoChu(26);
    (*boxThemSinhVien).cDoDayVien(3);
    boxXoaHet = new hopChu({1260, 134, 210, 40}, "         Xóa tất cả", RED, YELLOW, BLACK);
    (*boxXoaHet).cKieuChu(font28);
    (*boxXoaHet).cCoChu(26);
    (*boxXoaHet).cDoDayVien(3);
    boxTimKiem = new hopChu({70, 134, 400, 40}, "          Tìm kiếm", {173, 216, 230, 255}, YELLOW, BLACK);
    (*boxTimKiem).cKieuChu(font28);
    (*boxTimKiem).cCoChu(26);
    (*boxTimKiem).cDoDayVien(3);
}