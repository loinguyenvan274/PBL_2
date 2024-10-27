#include "bang.h"
#include "quanLy.h"
class cuaSoCon
{
    Bang *table;
    hop nutat;
    QuanLy<hopChu> nutBam;
    int chieuDai, chieuCao;
    int viTrix, viTriy;

public:
    cuaSoCon(const int &, const int &, const int &);
    Bang *lDCBang();
    void capNhatTT();
    void bieuDien();
    hopChu &operator[](const int &);
    ~cuaSoCon();
};