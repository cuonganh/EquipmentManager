#include <stdio.h>
#include <string.h>

struct ThietBi;
void hienThiDSTB(struct ThietBi *, int);
void hienThiTenCot();

struct ThietBi
{
	int maSo[10];
	char tenThietBi[20];
	char viTri[20];
	char nguoiQuanLi[20];
	char tinhTrang[20];
	char ngayNhap[10];
};

struct ThietBi nhapTB()
{

	struct ThietBi tb;

	printf("Nhap ma so: ");
	scanf("%d", &tb.maSo);
	printf("Ten: ");
	scanf("%s", &tb.tenThietBi);
	printf("Vi tri: ");
	scanf("%s", &tb.viTri);

	printf("Nguoi quan li: ");
	scanf("%s", &tb.nguoiQuanLi);
	printf("Tinh trang: ");
	scanf("%s", &tb.tinhTrang);
	printf("Ngay nhap: ");
	scanf("%s", &tb.ngayNhap);

	return tb;
}

void hienThiTTTB(struct ThietBi tb)
{
	printf("%-10d %-20s %-20s %-20s %-20s %-10s\n", tb.maSo, tb.tenThietBi, tb.viTri,
		   tb.nguoiQuanLi, tb.tinhTrang, tb.ngayNhap);
}

void sapXepTheoTen(struct ThietBi *ds, int sltb)
{
	int i, j;
	for (i = 0; i < sltb - 1; i++)
	{
		for (j = sltb - 1; j > i; j--)
		{
			if (strcmp(ds[j].tenThietBi, ds[j - 1].tenThietBi) < 0)
			{
				struct ThietBi tb = ds[j];
				ds[j] = ds[j - 1];
				ds[j - 1] = tb;
			}
		}
	}
}

void sapXepTheoMaSo(struct ThietBi *ds, int sltb)
{
	int i, j;
	for (i = 0; i < sltb - 1; i++)
	{
		for (j = sltb - 1; j > i; j--)
		{
			if (ds[j].maSo > ds[j - 1].maSo)
			{
				struct ThietBi tb = ds[j];
				ds[j] = ds[j - 1];
				ds[j - 1] = tb;
			}
		}
	}
}

void timTheoTen(struct ThietBi *ds, int sltb)
{
	char key[20];
	printf("Nhap ten: ");
	scanf("%s", key);
	hienThiTenCot();
	int i, timTB = 0;
	for (i = 0; i < sltb; i++)
	{
		if (strcmp(key, ds[i].tenThietBi) == 0)
		{
			hienThiTTTB(ds[i]);
			timTB = 1;
		}
	}
	if (timTB == 0)
	{
		printf("Khong co thiet bi %s trong danh sach!\n", key);
	}
}

void ghiFile(struct ThietBi *ds, int sltb)
{
	getchar();
	char fName[26];
	printf("Nhap ten file: ");
	gets(fName);
	FILE *fOut = fopen(fName, "a");
	int i;
	for (i = 0; i < sltb; i++)
	{
		struct ThietBi tb = ds[i];
		fprintf(fOut, "%-10d %-20s %-20s %-20s %-20s %-10s\n",
				tb.maSo, tb.tenThietBi, tb.viTri, tb.nguoiQuanLi, tb.tinhTrang, tb.ngayNhap);
	}
	fclose(fOut);
}

void docFile(struct ThietBi *ds, int *sltb)
{
	FILE *fOut = fopen("TB.txt", "r");
	int i = 0;
	if (fOut)
	{
		for (;;)
		{
			struct ThietBi tb;
			fscanf(fOut, "%10d %20s %20s %20s %20s %10s\n",
				   &tb.maSo, tb.tenThietBi, tb.viTri, tb.nguoiQuanLi, tb.tinhTrang, tb.ngayNhap);

			ds[i++] = tb;
			if (feof(fOut))
			{ // thoat chuong trinh
				break;
			}
		}
	}

	fclose(fOut);
	*sltb = i;
}

void hienThiTenCot()
{
	printf("------------------------------------------------------"
		   "------------------------------------------------------\n");
	printf("%-10s %-20s %-20s %-20s %-20s %-10s \n",
		   "Ma so", "Ten thiet bi", "Vi tri", "Nguoi quan li", "Tinh trang", "Ngay nhap");
}

void hienThiDSTB(struct ThietBi *ds, int slsv)
{
	hienThiTenCot();
	int i;
	for (i = 0; i < slsv; i++)
	{
		hienThiTTTB(ds[i]);
	}
	printf("------------------------------------------------------"
		   "------------------------------------------------------\n");
}

int main()
{
	struct ThietBi dstb[100];
	int sltb = 0;
	int luaChon;

	docFile(dstb, &sltb);
	printf("DANH SACH THIET BI:\n");
	hienThiDSTB(dstb, sltb);
	int i;

	do
	{
		printf("=============== MENU ===============");
		printf("\n1. Them thiet bi vao danh sach.");
		printf("\n2. Hien thi danh sach thiet bi.");
		printf("\n3. Sap xep theo ten.");
		printf("\n4. Sap xep theo ma so.");
		printf("\n5. Tim thiet bi theo ten.");
		printf("\n6. Ghi thong tin thiet bi ra file.");
		printf("\n0. Thoat chuong trinh.");
		printf("\nLua chon phim chuc nang: ");

		scanf("%d", &luaChon);
		struct ThietBi tb;

		switch (luaChon)
		{
		case 0:
			break;

		case 1:
			tb = nhapTB();
			dstb[sltb++] = tb;
			break;

		case 2:
			hienThiDSTB(dstb, sltb);
			break;

		case 3:
			sapXepTheoTen(dstb, sltb);
			printf("\nDanh sach thiet bi sau khi sap xep theo ten a-z:\n");
			hienThiDSTB(dstb, sltb);
			break;

		case 4:
			sapXepTheoMaSo(dstb, sltb);
			printf("\nDanh sach thiet bi sau khi sap xep theo ma so:\n");
			hienThiDSTB(dstb, sltb);
			break;

		case 5:
			timTheoTen(dstb, sltb);
			break;

		case 6:
			ghiFile(dstb, sltb);
			break;

		default:
			printf("Sai chuc nang, vui long chon lai!\n");
			break;
		}

	} while (luaChon);

	return 0;
}