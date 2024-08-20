#include "ROOT/InternalTreeUtils.hxx"
#include "ROOT/RDataFrame.hxx"
#include "ROOT/RDataSource.hxx"
#include "ROOT/RDF/RDatasetSpec.hxx"
#include "ROOT/RDF/RInterface.hxx"
#include "ROOT/RDF/RLoopManager.hxx"
#include "ROOT/RDF/Utils.hxx"
#include <string_view>
#include "TChain.h"
#include "TDirectory.h"
#include "RtypesCore.h" // for ULong64_t
#include "TTree.h"
#include "ROOT/RVec.hxx"
#include "TLegend.h"
#include <list>
#include <iostream>
#include <vector>
#include <string>
#include <TFile.h>
#include <array>


using namespace ROOT;


void print(const string &i) {
    cout << i << ' ';
}


int Plots1_Amax_Distb()
{
//gStyle->SetOptStat(0);
using namespace ROOT;


TCanvas *c1 = new TCanvas("c1", "Canvas on which to display our histogram");
int k = 1;

int batch = 4;

int p0, pf;

int n;
std::vector <string> Voltage_Sensor1;
std::vector <string> Voltage_Sensor2;

if (batch == 1){
//batch 1

//n = 5;


Voltage_Sensor1.push_back("107 V");
Voltage_Sensor1.push_back("112 V"); 
Voltage_Sensor1.push_back("117 V"); 
Voltage_Sensor1.push_back("122 V");
Voltage_Sensor1.push_back("127 V"); 

Voltage_Sensor2.push_back("130 V"); 
Voltage_Sensor2.push_back("135 V");
Voltage_Sensor2.push_back("140 V");
Voltage_Sensor2.push_back("145 V"); 
Voltage_Sensor2.push_back("150 V"); 

p0 = batch*100;
pf = p0 + 5;
} else if (batch ==2){ 
 //Batch2
 
//n = 6;


Voltage_Sensor1.push_back("125 V");
Voltage_Sensor1.push_back("128 V"); 
Voltage_Sensor1.push_back("131 V");
Voltage_Sensor1.push_back("134 V");
Voltage_Sensor1.push_back("137 V");
Voltage_Sensor1.push_back("140 V"); 


Voltage_Sensor2.push_back("300 V");
Voltage_Sensor2.push_back("330 V"); 
Voltage_Sensor2.push_back("360 V");
Voltage_Sensor2.push_back("390 V");
Voltage_Sensor2.push_back("420 V");
Voltage_Sensor2.push_back("450 V");

p0 = batch*100;
pf = p0 + 6;
} else if (batch == 3){
//Batch3

//n = 6;


Voltage_Sensor1.push_back("455 V");
Voltage_Sensor1.push_back("480 V");
Voltage_Sensor1.push_back("505 V");
Voltage_Sensor1.push_back("530 V");
Voltage_Sensor1.push_back("555 V");
Voltage_Sensor1.push_back("580 V"); 


Voltage_Sensor2.push_back("455 V");
Voltage_Sensor2.push_back("480 V");
Voltage_Sensor2.push_back("505 V");
Voltage_Sensor2.push_back("530 V");
Voltage_Sensor2.push_back("555 V");
Voltage_Sensor2.push_back("580 V");

p0 = batch*100;
pf = p0 + 6;
} else if(batch == 4){
//Batch4


Voltage_Sensor1.push_back("455 V");
Voltage_Sensor1.push_back("480 V");
Voltage_Sensor1.push_back("505 V");
Voltage_Sensor1.push_back("530 V");
Voltage_Sensor1.push_back("555 V");
Voltage_Sensor1.push_back("580 V"); 


Voltage_Sensor2.push_back("455 V");
Voltage_Sensor2.push_back("480 V");
Voltage_Sensor2.push_back("505 V");
Voltage_Sensor2.push_back("530 V");
Voltage_Sensor2.push_back("555 V");
Voltage_Sensor2.push_back("580 V");

p0 = batch*100;
pf = p0 + 6; 
}

std::cout << batch << endl;
std::cout << p0 << endl;
std::cout << pf << endl;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/*
for(int i = p0; i< pf; i++){
string str1 = "tree_merged_b";
string str2 = to_string(i);
string str3 = ".root";
string str4 = str1 + str2 + str3;

ROOT::RDataFrame df("tree_combined", str4);
auto m = df.Filter("ntrack==1");
auto n0 = m.Define("Amax_0", "Amax[0]");
//auto m0 = n0.Filter("20<Amax[0] && Amax[0]<300");
auto h0 = n0.Histo1D({"Amax MCP", "Amax [V] MCP", 150, 0, 500}, "Amax_0"); 
h0->SetLineColor(kRed);
k++;

auto legend = new TLegend(0.5,0.8,0.6,0.9);
legend->SetHeader("Amplitudes","C"); // option "C" allows to center the header
TLegendEntry* l0 = legend->AddEntry("h0", "Amax_0", "l");
l0->SetTextColor(k);

h0->DrawClone("SAME");
legend->Draw();
}

*/
string str5 = "Amax_0_Batch";
string str6 = to_string(batch);
string str7 = ".pdf";
string str8 = str5 + str6 + str7;

//const char* cxs = str8.c_str();

//c1->SaveAs(cxs); 


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


TCanvas *c3 = new TCanvas("c3", "Canvas on which to display our histogram");
int l = 1;
auto legend2 = new TLegend(0.5,0.8,0.6,0.9);
for(int i = p0; i< pf; i++){
string str1 = "tree_merged_b";
string str2 = to_string(i);
string str3 = ".root";
string str4 = str1 + str2 + str3;

ROOT::RDataFrame df("tree_combined", str4);
auto m = df.Filter("ntrack==1");
auto n2 = m.Define("Amax_2", "Amax[2]");
//auto m02 = n2.Filter("20<Amax[0] && Amax[0]<300");

auto m2 = n2;

//if (batch ==1){
//m2 = m02.Filter("60<Amax[2] && Amax[2]<300"); //Batch 1. Sensor 2
//} else if (batch ==2){
//m2 = m02.Filter("15<Amax[2] && Amax[2]<120"); //Batch 2. Sensor 2
//} else if (batch == 3){
//m2 = m02.Filter("8<Amax[2] && Amax[2]<60"); //Batch 3. Sensor 2
//} else if (batch == 4){
//m2 = m02.Filter("15<Amax[2] && Amax[2]<100"); //Batch 4. Sensor 2
//} 


auto h2 = m2.Histo1D({"Amax Sensor 2", "Amax Batch 4 [V] Sensor 2", 200, 0, 90}, "Amax_2"); 
h2->GetXaxis()->SetTitle("Amax [V]");
h2->GetYaxis()->SetTitle("Counts");
h2->SetLineColor(l); 



legend2->SetHeader("Amplitudes","C"); // option "C" allows to center the header

string strk = Voltage_Sensor2[l-1];
//std::cout << strl << endl;
const char* str22 = strk.c_str();
TLegendEntry* l0 = legend2->AddEntry("h2", str22, "l");
l0->SetTextColor(l);
string s = str22;
//legend->AddEntry("h2", str2, "l");
//legend->AddEntry(g, Sensor1[batch-1], "lp");
h2->DrawClone("SAME");
legend2->Draw("SAME");
l++;
}

string str11 = "Amax_2_Batch";
string str12 = str11 + str6 + str7;

const char* cxz = str12.c_str();

c3->SaveAs(cxz);


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


TCanvas *c2 = new TCanvas("c2", "Canvas on which to display our histogram");
int j = 1;
auto legend = new TLegend(0.5,0.8,0.6,0.9);
for(int i = p0; i< pf; i++){
string str1 = "tree_merged_b";
string str2 = to_string(i);
string str3 = ".root";
string str4 = str1 + str2 + str3;

ROOT::RDataFrame df("tree_combined", str4);
auto m = df.Filter("ntrack==1");
auto n1 = m.Define("Amax_1", "Amax[1]");
//auto m01 = n1.Filter("20<Amax[0] && Amax[0]<300");

auto m1 = n1;

//if (batch ==1){
//m1 = m01.Filter("60<Amax[1] && Amax[1]<300"); //Batch 1. Sensor 1
//} else if (batch ==2){
//m1 = m01.Filter("60<Amax[1] && Amax[1]<250"); //Batch 2. Sensor 1
//} else if (batch == 3){
//m1 = m01.Filter("10<Amax[1] && Amax[1]<60"); //Batch 3. Sensor 1
//} else if (batch == 4){
//m1 = m01.Filter("15<Amax[1] && Amax[1]<100"); //Batch 4. Sensor 1
//}

auto h1 = m1.Histo1D({"Amax Sensor 1", "Amax Batch 4 [V] Sensor 1", 200, 0, 90}, "Amax_1"); 
h1->GetXaxis()->SetTitle("Amax [V]");
h1->GetYaxis()->SetTitle("Counts");
h1->SetLineColor(j);

legend->SetHeader("Amplitudes","C"); // option "C" allows to center the header
//string strj = Voltage_Sensor1[j];
string strk = Voltage_Sensor1[4];
const char* str22 = strk.c_str();
TLegendEntry* l0 = legend->AddEntry("h1", str22, "j");
l0->SetTextColor(j);
string s = str22;
//legend->AddEntry("h1", str2, "j");
h1->DrawClone("SAME");
legend->Draw("SAME");
j++;
}

string str9 = "Amax_1_Batch";
string str10 = str9 + str6 + str7;

const char* cxx = str10.c_str();

c2->SaveAs(cxx);



return 0;
}


