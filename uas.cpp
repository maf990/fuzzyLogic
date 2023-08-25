//
//  main.cpp
//  fuzzy
//
//  Created by Hanny Haryanto on 21/06/23.
//

#include <iostream>
#include <iomanip>

using namespace std;

void fuzzification(float x, float a, float b, float c, float &u1, float &u2, float &u3)
{
    float uLeft;   // membership value for half trapezoid (left)
    float uCenter; // membership value for trapezoid
    float uRight;  // membership value for half trapezoid (right)

    float left_c, left_d;      // c, d value for left trapezoid
    float ctr_a, ctr_b, ctr_c; // a,b,c, d value for center triangle
    float right_a, right_b;    // a,b value for right trapezoid

    left_c = a;
    left_d = b;
    ctr_a = a;
    ctr_b = b;
    ctr_c = c;
    right_a = b;
    right_b = c;

    // left trapezoid
    if (x <= left_c)
        uLeft = 1;
    if (x > left_c && x < left_d)
    {
        uLeft = (left_d - x) / (left_d - left_c);
    }
    if (x >= left_d)
        uLeft = 0;

    // cout << "uLeft : " << uLeft << endl;   //to be replaced
    u1 = uLeft;

    // center triangle
    if (x <= ctr_a || x >= ctr_c)
        uCenter = 0;
    if (x > ctr_a && x < ctr_b)
    {
        uCenter = (x - ctr_a) / (ctr_b - ctr_a);
    }
    if (x == ctr_b)
        uCenter = 1;
    if (x > ctr_b && x < ctr_c)
    {
        uCenter = (ctr_c - x) / (ctr_c - ctr_b);
    }
    // cout << "uCenter : " << uCenter << endl;//to be replaced
    u2 = uCenter;

    // right trapezoid
    if (x <= right_a)
        uRight = 0;
    if (x > right_a && x < right_b)
    {
        uRight = (x - right_a) / (right_b - right_a);
    }
    if (x >= right_b)
        uRight = 1;
    // cout << "uRight : " << uRight << endl;//to be replaced
    u3 = uRight;
}

void and_rules(float f1, float f2, float temp, float &conclusion)
{
    if (f1 >= f2)
        temp = f2;
    else
        temp = f1;
    if (temp >= conclusion)
        conclusion = temp;
}

void determine_sample(float a, float b, float c, float &s11, float &s12, float &s13, float &s21, float &s22, float &s23, float &s31, float &s32, float &s33)
{ // from output fuzzy
    s11 = a;
    s12 = s11 - 1;
    s13 = s12 - 1;
    s21 = b;
    s22 = s21 + 1;
    s23 = s21 - 1;
    s31 = c;
    s32 = s31 + 1;
    s33 = s32 + 1;
}

void defuzzification(float u1, float u2, float u3, float s11, float s12, float s13, float s21, float s22, float s23, float s31, float s32, float s33, float &result)
{
    result = (((u1 * (s11 + s12 + s13)) + (u2 * (s21 + s22 + s23)) + (u3 * (s31 + s32 + s33))) / ((u1 * 3) + (u2 * 3) + (u3 * 3)));
}

int main()
{
    float x_lebarjalan, sempit, sedang, lebar;                                                      // lebar jalan
    float x_hambatan, rendah, normal, tinggi;                                                       // hambatan samping
    float lancar, ratarata, macet;                                                                  // kesimpulan potensi
    float sample11, sample12, sample13, sample21, sample22, sample23, sample31, sample32, sample33; // for defuzzification
    float potensi;
    string enter; // potensi outcome
    cout << fixed << setprecision(2);

    cout << "Masukkan x untuk lebar jalan : ";
    cin >> x_lebarjalan;
    cout << "Masukkan x untuk hambatan samping : ";
    cin >> x_hambatan;
    fuzzification(x_lebarjalan, 7, 14, 21, sempit, sedang, lebar); // lebar jalan
    fuzzification(x_hambatan, 5, 10, 20, rendah, normal, tinggi);  // hambatan

    cout << "Fuzzification lebar jalan : " << endl;
    cout << "sempit = " << sempit << endl;
    cout << "sedang = " << sedang << endl;
    cout << "lebar = " << lebar << endl;

    cout << "\n";

    cout << "Fuzzification hambatan : " << endl;
    cout << "rendah = " << rendah << endl;
    cout << "normal = " << normal << endl;
    cout << "tinggi = " << tinggi << endl;

    // rules
    and_rules(sempit, rendah, ratarata, ratarata);
    and_rules(sempit, normal, ratarata, ratarata);
    and_rules(sempit, tinggi, macet, macet);
    and_rules(sedang, rendah, lancar, lancar);
    and_rules(sedang, normal, ratarata, ratarata);
    and_rules(sedang, tinggi, macet, macet);
    and_rules(lebar, rendah, lancar, lancar);
    and_rules(lebar, normal, macet, macet);
    and_rules(lebar, tinggi, macet, macet);

    cout << "\nKeimpulan : " << endl;
    cout << "lancar = " << lancar << endl;
    cout << "rata-rata = " << ratarata << endl;
    cout << "macet = " << macet << endl;

    // sample for defuzzification
    determine_sample(5, 10, 24, sample11, sample12, sample13, sample21, sample22, sample23, sample31, sample32, sample33);
    cout << "\nSample value for defuzzification : " << endl;

    cout << "\n";
    cout << "Sample untuk " << lancar << endl;
    cout << "Sample 01 = " << sample11 << endl;
    cout << "Sample 02 = " << sample12 << endl;
    cout << "Sample 03 = " << sample13 << endl;

    cout << "\n";
    cout << "Sample untuk " << ratarata << endl;
    cout << "Sample 11 = " << sample21 << endl;
    cout << "Sample 12 = " << sample22 << endl;
    cout << "Sample 13 = " << sample23 << endl;

    cout << "\n";
    cout << "Sample untuk " << macet << endl;
    cout << "Sample 1 = " << sample31 << endl;
    cout << "Sample 2 = " << sample32 << endl;
    cout << "Sample 3 = " << sample33 << endl;

    // defuzzification
    defuzzification(lancar, ratarata, macet, sample11, sample12, sample13, sample21, sample22, sample23, sample31, sample32, sample33, potensi);
    cout << "\n\nPOTENSI :" << endl;
    cout << potensi << endl;
    cin >> enter;
    return 0;
}
