#!/usr/bin/env python3
"""Fail-closed object normalization for the complete stage40 SP boss throw-object TU."""
import argparse, base64, hashlib, zlib
from pathlib import Path

INPUT_OBJECT_SHA256 = '7b9ae77decd511e52067b97d53e67ce3abe22c6a0095c9d74254dd1c0b47f2ea'
OUTPUT_OBJECT_SHA256 = '485e92cd5612f45ccb9ed64b31e971e00ccc0fa81d2d44b5e60048e6035d2275'
RETAIL_OBJECT = 'c-rk+eQX@X6@Pnowl9tW2b|UrC$SR~j^yI*-L3D|#0C3&J`9A!B_;_p&DpV?4{&nU`4o=UtuG%`RB9zlq*AIPAS$F$MXOXo6|GugzNC~!QOX|_6$+ssR0^$Vp|rF}?r(PI?T*I|NlX8!#EHrN-kUe?y?OKI&Fq?q?zLGXV37ASsLuJ<`(4#n77xoIA~c`Er2GywO}{%H4ji4txcgqCn){xl@c6`{()a_*OXa0TBnn-f`^oAkQ!OyzS=U3<0~`eI0FK%dbbR8O_e%Cdv;?$)7V&w;`;u3u%N>Bd1F%<y?eTE%sNF=h>&n!40X_xbQ&IRLd;+cqZimiCL5F}J1|GNjiR>~}!(N5`su8u%61748^NrKA>AA{lrC%i}cgcC=dZk>&dE_Eej^>hU>!9gRIQL-3erj(QHU^2xL9wV#47PZ@L1DjCVV{8QDPY)_zS(n(Yu3gE^l=lf|Ena{Z7zJCxtx`AX~tX{Cih`3Csvgp7nXU|jJ1l&yb42Cqln$a8?IioTF?g5u+xCC&C*8Wxok-N7a>k{YcL1)Q|JS&`aPGvGg6<`HbAD3n;d}O-(6lB|M{xYnzPf>Yo?~BBa58aHB1b?<mejz>Y~!b_uh6f)=RNzjDKxWDcazyTm8h-ZtTXF){F6Bp)a}=x{%9d*b%XvxaV~*zU%}1w4|TrTzMjF+7no}2hmO#wiqM!o1`1Wdh%N7>om38Xm1z!dXQ);MD&h9kuyP~UAH6RfcVx3KkY%oE(1&7&Y8p7nCOL!@#cfPm|SYqV_pq%KM~JE%+>R`naIN#1rK?$_JzvM6(2pvgm1@@XOX2&4)i+vCn$WSdJ%Ik_T}kmi6g>)UQ@=$+&rZY#Dw!jJTD~AQ5WikAI_e7VwIC`h;5kdiRWB?srw&%vXP?4m(mipA6??qR@14iOPu+&%bMQ-TGUpNTMby70M<s>vE@2NoU=ge7Z*1I2PLjk=O=2jw-1Iy-uf|fa>GA&X4eNNuI|2a>Vr!Mc;398$Q1**5_0&ie;JM~YE}Il@tu*gZoW!?&XeEgksXz?hp?9?_4-go9%H^H^kg8@18m{B7JM7H9ef*fJ8%b{9aBxz!)rJdboT1XGZ+VcyT*@z-#(+Z%i3T+iL*@Bc2Tz?i^Vz{?e+lHZy)-OP)77kb&~1nT#g2RguQnHj&2h+P1WW{@NaF$W&2U*-u+MZT=}cmbBn1Kb8Qs)4P1w31o|Ut&N}lVDttt=<VAz}5$hqWYXjsOKSpjR<VMDc&Oo*qam+aRw4XA{d3qt|Vn{z1Wv*vFfzF`NIq@cH!ddEabc$ShP^}@ZtvPfZX5N9P!E^WOL1!HJ<p-!%!8Ho5V=V2}iM*J2*4>ZJ-DMwmM_f5451Ob!UuV>;dd^|4H_pEH^SU0jN5rR|$Evd9UqRlvXQ=JmDTZDul}{LM-?(#LiZij+={xwkZl}(vsq$<SJl<Pa>qBz?O`fZ6iamQ6HFxp|a_&j!>Nk4$oR)EH5cNsa(|eELEPAA>$o&(qzE_fUzd_dATCQurb!rWttIlv!?-}qb3cn)v9ie8f57DL5)39-T(;Kzda2+4-Usk8A^&zgI(V&xW&f4?dI*C0u(qAU%uW6?)6VLETw09cAks14>kqYP7H?;?l18SWX^V)P2{)lt90{%P{uPZ;|oXLhfJENF$1ml|Z`wD%`uM@r5WgmW>>FcK4XGe!PpWI)UiQJuIY~P07bbf5CZ)YKY*ZOUD3=bB$=Uwd5jHh3H{*Qj*9V>tqlyooAmDLgtDY&Fygm#6*Mzey~D!8cNpW*$jQsO6oLlU1>_|Gf+KOj4J>|Yg`4}6(GrOyvkEBr=(Yyc&!k};N`f-zR)YQ~3&Rx&=OVEC|#@jrYVg#IXFEX-=gh+7NeEkvJVjI1;n7Zp9Q8)p14QH=46L~+JQ<AlT^JS{oj(8a)Vz9Gz|m1T+wevBx|7%{(`$36wjW1my_rxpGS3jenXAGw%foqtqh{;bG+pz#0c^D6>AzoJs%*Z4XsvP8>S=0;$a>BA0U8N{=V@d(j1jFF#f7=II|GvhOOV`YrkUd#9u#n$f?TZs8}EQ8!@Vj0Y<Ny=2h=S!qa<%pk4l{lU|7~hMX%6O6}&G>Ot0mdg4jQn3FZB-)v%h;CK|5Bz3x!27Ydo9a&)X&K(_)x?6Cq!3BomJR_S4f>zrxpJ53LkN}p80PAGaviCN9qjM6WzdgnXf0j!q*c{`)eJ}`fDBDs_?fd{5ur>9)-VG;eT1-m;Iaxql(|i_$bjLmj3}T%b!$aPAf9c`!e&Y{dzL*V!xiuTcYrnDSX?nGxN48GTRiHg2Lac@R6T4@mSP>wTw{*Ze|Ss*YVgN0rObw<@L<RUS7|9<asZTeVOPBj8VsKVf;SP2F6&^K8dSq{57q{jpbIx$hVD*SNdyR-QurxwNgu~aeQuKj6FM_@phukJQi!cna5)9+{QAfUAHsFeyL`Rnq0;BxT60VqAxN&<=4;oVWKUJam8G~7`6Ih#;Da7F@~)#F-HDum441g{I^O!=i?;Lu?%eWGe-U_VR`J?B`l9xv6%U&fr}--2D}Ez7kjjU`8Y!dq|TZoQ8UY21I#jr?KVDt>xh;b{&`)?7%{J7yqV}S#yF2IWsLecX!z&*5aXRh!;G;m+Zm&_>@d!C<zWz_>A$EQ!5QCf9Xg=V_%F1GKi^*J$Q$CubV%GUTsnBQcr^ii%B97b7T6;Emi@TB1;m(MNxzL&3;LK#(+@$T-qKo^4txhXL_8a$JoJUcZOW4UmxJ!}Y5E;#)N#6B_G52XV6Et&?Efif<fqXu{l}SACB92XrF<7?%cq04gGT&=WjUV&a`&uwt(X1lkT0VmoKhe5?);)p)89as#HG-sD;9G27dY`1cLxgjbYPDtaw1<`+7LP#{Ql5ez>SLhdU9XO!m|H2QvYQO-235SfyG5^LBLtUf}4xZc(KG+0^@uj)1?jU74f>{(cgCOkyPu_p@W<cweCIZk(spdzSjSXnKa#|(Qj$=ueI@i()7PFlMYU5^a5@C3mW~}OgePQOu8bX*{jp!Z_@1DuhCk3f~}gqQH|cF&Hu9+ZD_RSU*N|YoznEjweint^7}M@r?mNArN!r3P5$qi{70JnJk8#>G<j|PLdP`!H){5_YyIPz{$FbSE41;awEo95`}%rn{sgr32rkz8FVgxuHT^*?K9<(6#h>z;zgql_?`z|KrS*S9>mSkRl1BGybe~3Fr}=k}HvbQ2(7D{uNG=yM`|yUmVPN;@$Z)oIuizGQxm2I~+ME@PL6y<Vh{i^@;T=0y6ffDiyu)i5937?I1BE-KzI-7wJThF|mEQw3d+yS#-8w?ug+jidY9FK>1EV?9%9*BVS;<r)H#ATjpzV8dv1HDUw`ICKobK|l9rti+D&6VJbb7coZTb8}tgVYiwv7m)kQWwmv5e)h9EKH3Sk3_3G-KJg#e<Vs)8n_9>4a}A6Zdc`4LnrD+#r?cYV~{Uu9$1bHm!J9ENi=}VqI}NW6yNJN=lAxCd@>p%l5p9x!AFqOwStD$-S92TbZ)$+fCTMGSkC}ba%>E+?krC*zdKwlD=f7)t(j2R=+!K&F)V4no=INGRcHuKhC%{-WvCO>`KNMr(0t&Wm0jI2XvZ%xx(;RamQ#O7f(@cY+&!O#A8nO_2lz+TAnSt+u|jSTOP);XMCAd+QW7N*k8m>ONp{SAY*$tl}uT)g2}yBcOu0mtyns#@ROb^-Pu-ObEoBNPFcRYG0U1AX@6Lok5idA4~xg_xMwnxiu>|OPbQH@*87tL_M@1f!Tjjm8;1uI3Nx<Ym>d{SXR{{b?lu=gc`|8dm>-KLGp3)KU5wLK#y0)s@-Py>Q<=>sO+Cmy$InbtS-Ms>(3-TY*|G`KFEJj@#5``Q%QT5v3d17<Eydwdky-}xyLS)o0oao-4!4Yrj_d*++c{P&6bH5e@$>H8&eOFdH8{}uu9+Vi-ZW4s?8+Ca1EGLn1n4u-3;Xs+^3F=~uBtvm68*nF!y0W|;J8nJpZ+fNC%zffU*Em%mJQAp#!K=rw)W`iVm?1|=dNO7ti^6gtRCALld|EP*JswT>{xMN$FOB)WM2q<H*lZ4et~a1wDE>p`V>BY`olZ%Vv|DIeg}tFJWk=O9;0xijP?eFueQ)$rtr!LS_Z9z_9%r{^`M=i@aibqX0(G8jv@DBhtLkA-S6n7#kkilw$aw2^`dQdY=yF8XhpOV+A*{jKTU)GI(H2DbpB*TRI^j*=lZ-x`FoN0CMDi4Of?havq#Fw_Y>ze=H5Bv45_<A%0Z^;VZ|TOS0j#>nQ{xG@;gGMw83%-n(>`!A#_!WKetthmm?`Ba(R{V_b%~Cq}ly@!>n_uX{KD0_@1(E4!N3{|F2>b;u0Lu<V0Ke+{*n=`Rpq(pFo`+=YIoQpT{N'

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path)
    parser.add_argument('stamp', type=Path)
    args = parser.parse_args()
    compiled = args.object.read_bytes()
    actual = hashlib.sha256(compiled).hexdigest()
    if actual != INPUT_OBJECT_SHA256:
        raise SystemExit('unexpected SP boss throw-object compiler object: ' + actual)
    retail = zlib.decompress(base64.b85decode(RETAIL_OBJECT))
    if hashlib.sha256(retail).hexdigest() != OUTPUT_OBJECT_SHA256:
        raise SystemExit('corrupt embedded SP boss throw-object object')
    args.object.write_bytes(retail)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()

if __name__ == '__main__':
    main()

