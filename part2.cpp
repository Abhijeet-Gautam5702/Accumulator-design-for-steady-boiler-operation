#include <bits/stdc++.h>
using namespace std;
ofstream out("output_b.txt");
ifstream in("input.txt");

/*
CLL121 CODING PROJECT [PART-2]
*/

float p1, p2, m1, m2, t, p_i, p_f, a_i, a_f;

// declaring the STEAM TABLE (using unordered maps)
unordered_map<int, float> V_l;
unordered_map<int, float> V_v;
unordered_map<int, float> U_l;
unordered_map<int, float> U_v;
unordered_map<int, float> H_l;
unordered_map<int, float> H_v;

void STEAM_TABLE()
{
    // Volume of sat. liq. at different pressures
    for (int i = 700; i <= 1000; i += 50)
    {
        V_l[i] = 0.0011;
    }
    // Volume of sat. vapor at different pressures
    V_v[700] = 0.273, V_v[750] = 0.255, V_v[800] = 0.24, V_v[850] = 0.229, V_v[900] = 0.215, V_v[950] = 0.204, V_v[1000] = 0.194;
    // Enthalpies of sat. liq. at different pressures
    H_l[700] = 697.1, H_l[750] = 709.3, H_l[800] = 720.9, H_l[850] = 732, H_l[900] = 742.6, H_l[950] = 752.8, H_l[1000] = 762.6;
    // Enthalpies of sat. vapor at different pressures
    H_v[700] = 2762, H_v[750] = 2765, H_v[800] = 2768, H_v[850] = 2770, H_v[900] = 2772, H_v[950] = 2774, H_v[1000] = 2776;
    // Internal Energies of sat. liq. at different pressures
    U_l[700] = 696.33, U_l[750] = 708.475, U_l[800] = 720.02, U_l[850] = 731.065, U_l[900] = 741.61, U_l[950] = 751.755, U_l[1000] = 761.5;
    // Internal Energies of sat. vapor at different pressures
    U_v[700] = 2570.9, U_v[750] = 2573.75, U_v[800] = 2576, U_v[850] = 2575.35, U_v[900] = 2578.5, U_v[950] = 2580.2, U_v[1000] = 2582;
    return;
}

// function for interpolation of the values from the steam table
float interpolate(float x1, float y1, float x2, float y2, float x)
{
    float res = y1 + (float)((y2 - y1) * (x - x1)) / (x2 - x1);
    return res;
}

float g1(float p, float a)
{
    float res;
    // if the pressure value exists in the steam table, no need of interpolation
    if (V_v.count(p))
    {
        res = (float)a / (V_l[p]) + (float)(1 - a) / (V_v[p]);
    }
    else
    {
        // interpolation needed
        float V_vap, V_liq;
        V_liq = 0.0011;
        if (p > 700 && p < 750)
        {
            V_vap = interpolate(700, V_v[700], 750, V_v[750], p);
        }
        else if (p > 750 && p < 800)
        {
            V_vap = interpolate(750, V_v[750], 800, V_v[800], p);
        }
        else if (p > 800 && p < 850)
        {
            V_vap = interpolate(800, V_v[800], 850, V_v[850], p);
        }
        else if (p > 850 && p < 900)
        {
            V_vap = interpolate(850, V_v[850], 900, V_v[900], p);
        }
        else if (p > 900 && p < 950)
        {
            V_vap = interpolate(900, V_v[900], 950, V_v[950], p);
        }
        else if (p > 950 && p < 1000)
        {
            V_vap = interpolate(950, V_v[950], 1000, V_v[1000], p);
        }
        res = (float)a / (V_liq) + (float)(1 - a) / (V_vap);
    }
    return res;
}

float g2(float p, float a)
{
    float res;
    // if the pressure value exists in the steam table, no need of interpolation
    if (V_v.count(p))
    {
        res = (float)(a * U_l[p]) / (V_l[p]) + (float)((1 - a) * U_v[p]) / (V_v[p]);
    }
    else
    {
        // interpolation needed
        float V_vap, V_liq, U_liq, U_vap;
        V_liq = 0.0011;
        if (p > 700 && p < 750)
        {
            V_vap = interpolate(700, V_v[700], 750, V_v[750], p);
            U_vap = interpolate(700, U_v[700], 750, U_v[750], p);
            U_liq = interpolate(700, U_l[700], 750, U_l[750], p);
        }
        else if (p > 750 && p < 800)
        {
            V_vap = interpolate(750, V_v[750], 800, V_v[800], p);
            U_vap = interpolate(750, U_v[750], 800, U_v[800], p);
            U_liq = interpolate(750, U_l[750], 800, U_l[800], p);
        }
        else if (p > 800 && p < 850)
        {
            V_vap = interpolate(800, V_v[800], 850, V_v[850], p);
            U_vap = interpolate(800, U_v[800], 850, U_v[850], p);
            U_liq = interpolate(800, U_l[800], 850, U_l[850], p);
        }
        else if (p > 850 && p < 900)
        {
            V_vap = interpolate(850, V_v[850], 900, V_v[900], p);
            U_vap = interpolate(850, U_v[850], 900, U_v[900], p);
            U_liq = interpolate(850, U_l[850], 900, U_l[900], p);
        }
        else if (p > 900 && p < 950)
        {
            V_vap = interpolate(900, V_v[900], 950, V_v[950], p);
            U_vap = interpolate(900, U_v[900], 950, U_v[950], p);
            U_liq = interpolate(900, U_l[900], 950, U_l[950], p);
        }
        else if (p > 950 && p < 1000)
        {
            V_vap = interpolate(950, V_v[950], 1000, V_v[1000], p);
            U_vap = interpolate(950, U_v[950], 1000, U_v[1000], p);
            U_liq = interpolate(950, U_l[950], 1000, U_l[1000], p);
        }
        res = (float)(a * U_liq) / (V_liq) + (float)((1 - a) * U_vap) / (V_vap);
    }
    return res;
}

int main()
{
    in >> p1 >> p2 >> m1 >> m2 >> t >> p_i >> a_i;

    // creating the steam table
    STEAM_TABLE();

    float A = (m1 - m2) * t, B = t * (m1 * H_v[p1] - m2 * H_v[p2]);
    float c1 = g1(p_i, a_i), c2 = g2(p_i, a_i);

    float Vacc = pow(10, 5); // a very high value is taken initially and this will be modified with each iteration

    // loop iterates over each value of pressure and finds value of corresponding a_f & Vacc.
    // range of pressure is from [p2+100, p1-50]
    for (float p = p2 + 100; p <= p1 - 50; p++)
    {
        float V_vap, V_liq, U_vap, U_liq;
        int x1, x2;
        // this loop is used for interpolation of properties at various intermediate pressures
        for (int t = 700; t <= 950; t += 50)
        {
            if (p >= t && p <= t + 50)
            {
                x1 = t, x2 = t + 50;
                break;
            }
        }
        V_vap = interpolate(x1, V_v[x1], x2, V_v[x2], p);
        U_vap = interpolate(x1, U_v[x1], x2, U_v[x2], p);
        U_liq = interpolate(x1, U_l[x1], x2, U_l[x2], p);
        V_liq = 0.0011; // liquid is incompressible

        // values of various terms used in the calculation of a_f for each pressure value
        float coeff = (float)B * (1 / V_liq - 1 / V_vap) - (float)A * (U_liq / V_liq - U_vap / V_vap);
        float term = (float)B / V_vap - (float)A * U_vap / V_vap;
        float c3 = B * c1 - A * c2;

        float a_f_curr = (c3 - term) / coeff;                          // current value of a_f for this particular pressure-value
        float Vacc_curr = (float)A / (g1(p, a_f_curr) - g1(p_i, a_i)); // Vacc for current pressure-value
        // modifying the Vacc value if a minimum value is found. Correspondingly, a_f & p_f values are also modified.
        if (abs(Vacc_curr) < Vacc)
        {
            Vacc = Vacc_curr;
            a_f = a_f_curr;
            p_f = p;
        }
    }

    out << "Vacc = " << Vacc << " m^3" << endl;
    out << "a_f = " << a_f << endl;
    out << "p_f = " << p_f << " kPa" << endl;

    return 0;
}