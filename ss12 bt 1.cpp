#include <stdio.h>
#include <string.h>

#define MAX_NV 50

struct NhanVien {
    int maNV;
    char hoTen[50];
    int soPhutDiMuon;
    float luongCoBan;
};

int timTheoMaNV(const struct NhanVien ds[], int soLuong, int maNV);
int themNhanVien(struct NhanVien ds[], int soLuong);
void hienThiDanhSach(const struct NhanVien ds[], int soLuong);
void capNhatPhutDiMuon(struct NhanVien ds[], int soLuong);
void timKiemNhanVien(const struct NhanVien ds[], int soLuong);

int main() {
    struct NhanVien ds[MAX_NV];
    int soLuong = 0;
    int choice;

    do {
        printf("\n===== H? TH?NG QU?N LÝ CH?M CÔNG HRM =====\n");
        printf("1. Thêm nhân viên m?i\n");
        printf("2. Hi?n th? danh sách và tính luong\n");
        printf("3. C?p nh?t s? phút di mu?n\n");
        printf("4. Tìm ki?m nhân viên theo mã\n");
        printf("0. Thoát\n");
        printf("==========================================\n");
        printf("Nh?p l?a ch?n: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                soLuong = themNhanVien(ds, soLuong);
                break;
            case 2:
                hienThiDanhSach(ds, soLuong);
                break;
            case 3:
                capNhatPhutDiMuon(ds, soLuong);
                break;
            case 4:
                timKiemNhanVien(ds, soLuong);
                break;
            case 0:
                printf("Ðang thoát chuong trình...\n");
                break;
            default:
                printf("L?a ch?n không h?p l?! Vui lòng ch?n l?i.\n");
        }
    } while (choice != 0);

    return 0;
}

int timTheoMaNV(const struct NhanVien ds[], int soLuong, int maNV) {
    for (int i = 0; i < soLuong; i++) {
        if (ds[i].maNV == maNV) {
            return i;
        }
    }
    return -1;
}

int themNhanVien(struct NhanVien ds[], int soLuong) {
    if (soLuong >= MAX_NV) {
        printf("Danh sách nhân viên dã d?y (t?i da 50)!\n");
        return soLuong;
    }

    int ma;
    printf("Nh?p mã nhân viên: ");
    scanf("%d", &ma);

    if (timTheoMaNV(ds, soLuong, ma) != -1) {
        printf("Mã nhân viên dã t?n t?i trong h? th?ng!\n");
        return soLuong;
    }

    ds[soLuong].maNV = ma;
    while (getchar() != '\n');

    printf("Nh?p h? và tên nhân viên: ");
    fgets(ds[soLuong].hoTen, sizeof(ds[soLuong].hoTen), stdin);
    ds[soLuong].hoTen[strcspn(ds[soLuong].hoTen, "\n")] = 0;

    do {
        printf("Nh?p s? phút di mu?n: ");
        scanf("%d", &ds[soLuong].soPhutDiMuon);
        if (ds[soLuong].soPhutDiMuon < 0) {
            printf("S? phút di mu?n không du?c âm!\n");
        }
    } while (ds[soLuong].soPhutDiMuon < 0);

    do {
        printf("Nh?p luong co b?n: ");
        scanf("%f", &ds[soLuong].luongCoBan);
        if (ds[soLuong].luongCoBan < 0) {
            printf("Luong co b?n không du?c âm!\n");
        }
    } while (ds[soLuong].luongCoBan < 0);

    printf("Thêm nhân viên thành công!\n");
    return soLuong + 1;
}

void hienThiDanhSach(const struct NhanVien ds[], int soLuong) {
    if (soLuong == 0) {
        printf("Danh sách nhân viên dang r?ng!\n");
        return;
    }

    printf("\n--- DANH SÁCH NHÂN VIÊN ---\n");
    printf("%-7s | %-15s | %-11s | %-15s\n", "Ma NV", "Ho ten", "Phut muon", "Luong thuc nhan");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < soLuong; i++) {
        float tienPhat = (ds[i].soPhutDiMuon > 15) ? 50000.0f : 0.0f;
        float luongThucNhan = ds[i].luongCoBan - tienPhat;

        printf("%-7d | %-15s | %-11d | %.0f\n",
            ds[i].maNV,
            ds[i].hoTen,
            ds[i].soPhutDiMuon,
            luongThucNhan);
    }
    printf("------------------------------------------------------------\n");
}

void capNhatPhutDiMuon(struct NhanVien ds[], int soLuong) {
    if (soLuong == 0) {
        printf("Danh sách nhân viên dang r?ng!\n");
        return;
    }

    int ma;
    printf("Nh?p mã NV c?n c?p nh?t: ");
    scanf("%d", &ma);

    int idx = timTheoMaNV(ds, soLuong, ma);
    if (idx == -1) {
        printf("=> Không tìm th?y nhân viên!\n");
        return;
    }

    int phutMoi;
    do {
        printf("Nh?p s? phút di mu?n m?i: ");
        scanf("%d", &phutMoi);
        if (phutMoi < 0) {
            printf("S? phút di mu?n không du?c âm!\n");
        }
    } while (phutMoi < 0);

    ds[idx].soPhutDiMuon = phutMoi;
    printf("=> C?p nh?t thành công!\n");
}

void timKiemNhanVien(const struct NhanVien ds[], int soLuong) {
    if (soLuong == 0) {
        printf("Danh sách nhân viên dang r?ng!\n");
        return;
    }

    int ma;
    printf("Nh?p mã nhân viên c?n tìm: ");
    scanf("%d", &ma);

    int idx = timTheoMaNV(ds, soLuong, ma);
    if (idx == -1) {
        printf("=> Không tìm th?y nhân viên!\n");
        return;
    }

    float tienPhat = (ds[idx].soPhutDiMuon > 15) ? 50000.0f : 0.0f;
    float luongThucNhan = ds[idx].luongCoBan - tienPhat;

    printf("\n--- THÔNG TIN NHÂN VIÊN ---\n");
    printf("Mã NV: %d\n", ds[idx].maNV);
    printf("H? tên: %s\n", ds[idx].hoTen);
    printf("S? phút di mu?n: %d\n", ds[idx].soPhutDiMuon);
    printf("Luong co b?n: %.0f\n", ds[idx].luongCoBan);
    printf("Luong th?c nh?n: %.0f\n", luongThucNhan);
}
