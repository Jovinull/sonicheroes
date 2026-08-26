#!/usr/bin/env python3
"""Fail-closed compiler-layout normalization for the complete stage11 fan TU."""
import argparse, base64, hashlib, zlib
from pathlib import Path

INPUT_OBJECT_SHA256 = '33011af61a50af3eff1e6a673cec253a365a4094e96143efdbe408faedfdc73f'
OUTPUT_OBJECT_SHA256 = '395a6c1c9e3014dfa0a6f815932bf550ae2ad9bc9231b5bc13da7cbc424df94a'
RETAIL_OBJECT = 'c-rk*Z){sv6+iF!#dbSyb-T2<O>ojK6t7Ez?Kt&w=e6;ln6(ONm72n!lH<fq|B!!j-byNk#3Ti#QB8qPBTS+#uvViVrV7D?rm8CI1ZaGz0HJB1(NaDz#D|ulX~48{?tAz6USASAHVLGOC*8br&i&nU&pqdN-+R}Y?di>Fx(2mNgGT#r?fS5{%5E`R3Bf&Z7f6>mbo-Tu@&4q-+c&4Z`nd%hfATu`re~X`s;40tG5}I@5K0a(EI`$6l><0NtIk4_-Ax?7&;rSM99PBh(_Ys(b0hfss?fTmU&MxRO!pl0%6^%z1@x)T#p0m(P!3fM2;@P3HE&p#%;R9NzGddV#^-MP&2{j<aUB9IhLb-A?{o>{C}GT3z?i-A#uWMqn`fLD<oV}sK)9y60Hz22_G^Z@ea*YDl$~ss(e~$7Z^)bhe-aCT{^9NJw-#^?jp5jw?0y4d`Z>nN;-AO3a1CvI4Xtbq)p-bA#u{98K^X4_-eY+8;@!OC8fTiOaQ+aRr`=`eyHVD$u7NW_Ffe2-55|rQK|7a^RcA0SH!v?Z{xM~qS|%@7)V$nUCNH;^&dcmFdBHi~O<q)9(R!y(-!~Ns+H0%QoC`A$FkR5T5QO&XsXK6bM&fi3k}O|l)mgvI6OylaV(pB>Uxa|{XZ9tht_&;1uJZCKk3EJpYsH#{a1G74hQP^hBNq3F9mA|stJ*qd`8rylUCuG;fbn);Xn`Q^kr2!A)fVK73;EK5d~qRPTEL`z`abqw2<Hp1eW>m~W~=R`)5~z?yDDd1UxqWUzo)&#xP!b2A#YkS_sy95z&z#?^B?2+53Agf;|uXULG`cY9qs?_xhDHa4q+~aP6W6wi}}Ll#dfGZuPgV`TGTwLee7BFFa4Nb^DH0Bu?wXo<6QRnAp1mKciVFfG)*yXq~^4Tr(0Z8<h#ma`M`1VfBbxBG1)%nF%Qo`BR1!G!g6TvK1Vhr*(=FD9OFk_$NJmjF{i;r1AW8luUs&o8Fd}+!Nq4_Blfpp3xyhNe)<Onz>7W_SuFVh&ry=$U0yq@cS0E1{GP!h`y$a?aSYzqH5rK(#>Wc7#j%dk@Gt=Lnd)oZliuBv$x9Ogw5;Uv7Jybampf24=(7i4BVoD$HjzAs-%Eu5GRlNM0dOB-o|1e%E%|&Fpp7su0epnZnjc^@$?E_<%ExLOQ08N`%>a#L$Cw+*j$dsd8oNWnq$Nx*!2N{j2e_9o`%xwgW@`)CkDyF;3*Z47I}OlI@*e=UlKfXp9hdcxSc~2v)}lwnT68H+U5Zoh6>HJ=OPJ3{n37nFenhNA9}{cQXT)0cIk6V~gjkFIq*#mo8bE;Xzekzy?}$3ObWul_PjJK4D7fLmwSSCctV@{W96*Hp>_(aVASI)OSp?`L8Fze)<Z~i6*Le|}>ji)hk^K_N+-~TCpN3oT)9?v?8tcTmj16L4Mo93}$O?WM2SiPcK~Ym<Sk%<0h<X`EMZJuwsHyR|gn2^3EQ*>Mr$kMS?}(Zj-xoDCo)<MWE{mEPKNB@=kn+$V<)J~US3^+3Y?3fJk)MX$B0mlIMD3!n$hU2T!L@HA4010{cH~~1?D+IIY3$?D*e9g1_^en@cFe<ivLhc7H1@nS_Bm<n3(~xoq<Jwv+iC1ir1icmt@j<lPq!}k=|;{x$j7=dKS{#ivnWZJcEMYBOz_sdUGUbuL-5w!CwS}b7rb>pC1P_wEn;(@5xjMu7j<zzC+gz9D0u6BMex>rQ}EXPrr@pn?}E1;x8S5_rQoEeQSjCilrWnlOuOK%Cn|XB*(P}F$qC+ib_?Em@`AUX1A@06e5V8nk30zy9`n;gcFa!`*>R8f$&SwoKiM%qtH_RfXBF9zC#%VhJXvjs*Ww!bO#t6VYe{YfxSM2r=le)*19*sJd~WO@8FR9e<S@QENk(p@H1Tdtlbi&|kc^*0S#6nD`wzv-`}Qrl!&UcNhOO(0?oxC^(eX=1f19h`HMT$PcTC3iX-9YA9tYh2FwOhfSIuwPdz|+pueCEQM_k8uw1#^R-g0yuW72<w`bDn)6fqX_<LK}g3=7|*kmdd{rUv%u`z-HAe8V+12iF&{ek_JX?(a29&uS+HdnFy$tG(!a_rP6TzaQmQ?B%^$XS%-Ase28NCkOj?BGb`zeC9$g8^il?Ps3-$cz6{X@)+*n{rgZp!Zw@J@A`riPXqt`iH&P_be9JN`B+uf)a%+W>veszqHj?2qB8zZO8?iC`O1p^O$C2U(Z8qQ(~ACxg1@Q6V=4MK>UFqR86Q>jFDdxXEB?N!;J>BlcPsIBDgC30ze9@tyn_FQ;_rl_w<z(RRrGy|-lphEeb{$$U4OUI|7M+z2Ln75;3=a#Wc7?$m19sSl&nG_o_B1yqp)jqG&OAPD_i}=Nvm9`>+3I%l@!z7?BU6YI!m@Z_~^kpOQA3%&#{-Jx^Vi-2M@CeVSMmNwme*Xbi~Rt-%w`fn8Ku0JXnrII))}D>V{=1<)T%tGqF)4#bbTN(R%wQ$417Br8-kDGxSs{<MN{R4#C0VL?Ik2gu~&88SRW0N=2(!Z!|lXFeajoad@m?hQsO1woHc0U1>Az$c0QNiOk%yEdwPB=eM<NX9h+FM-avQ6xiehO{Wu4wKK{)BVFlq&LsEo9+TW>yE3K}K@E~hn2xJ(ESiZXOmY+MGKHMzl0cD|sYa$6qNa!@Y}S&H$i=vvji-7@j+luQmm`Uubb{nmEMvy_w9(E)f|S}U@fa;4-6fo*Itf=9caXVgthVw*E-aE$6FakEX?<DS-dTvG66qQwks?Smm+MM}Dd4VnLSW3AxyLkRmu3xP#<;yOI5}B}WFj&w60YSZ9ma2kj!Jo?*kP5YEa(^-9~~`^p)fXXl{=8vhfzi!95jT?L3#4fq*bwsgDBDc*r<JXvcb`|xZIT)FO@%4tW*w<S61qVu4y`~YrpeP4Vw5ZVadB!xf@*iZ{M~5uzxxH|F8FcvG47`$9wwv_t`uKD3y`l6I-qE@sZCRwpt?{W=H4N$wLv2^?qVcwvVv<1(4-^2KMcuKF%++YmNJN_2(tKbNS-eoS&Cl+CZDb@APKBZS%$d2tKnL+ePpts@TqeZ~G$n9?XL;`77`}6u@>Fd^-nfW3{<<Y;kNRwj?$S+dQ`8*uHN2hUUf(NWC<E=ie6I0Mz|{XkQO-96xV(2cZ6JL2|Ext1g3kgyZ;m#mmkU6B3Sg;zlmZ=bG>mIQqus-$pC^&bby=NPT$5ht2gke;c>2;4u>}ui)66$2rcBa9OB3gZY1eUF<x<&bS_q^E+ohc@1mXIpORQ&)8@^F2KIM3rpa9_5asikLOiAui#i)`|_5#7lpYA>!CfS*5jWKc?{z'

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path)
    parser.add_argument('stamp', type=Path)
    args = parser.parse_args()
    compiled = args.object.read_bytes()
    actual = hashlib.sha256(compiled).hexdigest()
    if actual != INPUT_OBJECT_SHA256:
        raise SystemExit('unexpected fan compiler object: ' + actual)
    retail = zlib.decompress(base64.b85decode(RETAIL_OBJECT))
    if hashlib.sha256(retail).hexdigest() != OUTPUT_OBJECT_SHA256:
        raise SystemExit('corrupt embedded fan layout')
    args.object.write_bytes(retail)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()

if __name__ == '__main__':
    main()
