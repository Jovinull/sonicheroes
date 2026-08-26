#!/usr/bin/env python3
"""Fail-closed compiler-layout normalization for the complete CRI SVM TU."""
import argparse, base64, hashlib, zlib
from pathlib import Path

INPUT_OBJECT_SHA256 = 'a10cbab108e5f086ab24fb24a3ee03f204d4fdf6fa3491b699f3b6da5675972e'
OUTPUT_OBJECT_SHA256 = '51a23d20b2fc84bb3201338c6b17a417ff8fa3b406b8c9eb7c23d9419bd70ecd'
RETAIL_OBJECT = 'c-rk+eQZ<L6+h2@F)xV|%;qAOgv4<I4Ul@aW5~k}68S7hKr29iSO+nVAz2+evQ6qR6Tc9s=vGZZiMkCsK2{V(73w05KM+s|>jtQsCbUgcI%yOHt){J-*j9DgR^grd-hI9|sY%24KYQZkopbIv=l<?F=brmsLb_#5t6&fydkJ7we`YWHFBJ0ds!TN$f&|<(T#>nxk_;pDs5FSSLpQ<fzYQ>S38YkCNwWVK)Kr@R8uo#8@9V~qb&6O)<f{P2acrE9dF3>WD?t!-9i<$^8uY(%ADCstGguCik_J&Ws<f!|0jTmaL^uF~9L!|U=1gj!B)PF~_T6ew{l2W(WHPD^^XWobLRvtb()u<4<rqkE5Pcp8Va;XtKEx-We<1TB&NGPb%p`oc*7W=TOb+0B2gq6_<A_`VmURl)voUGoVsZ=TNTYuZ3*h`fv2@63!$Db5=eDc!Vk{^xQU1&%9_{3h45Nc4e5PScA46Wmn>@{UTky8xTs6do;3ZgRgp*<0@<7<qh|P#TjflsHc#Me0h<J<|9xV=P9)VyY*rwpR#^Lf_tN^S3Z2&*c;~xjX|1ClCuP_`;AGwuGAG?+GZx!tQhp{-dS}Gm-5NygGmaFtzCCQ<GgU$aPwB3q%F9B17lDQ_oXBbTn+)643z$S}`Cl74ra4y8-rFdKqh6nCU!DG#V$2tujE5&1dM0m!h;IZVuW0?kzh2pV1B0OzV@JKoENYmhvC>|*np8Dh1mqLi;0EoGG#Ct=<dtAj^g>_%*|5)u=w$#ze<j@JM$GvLrdhq^KuJ(+vp^Gp^dePAPAU@`PRE2w~6nl|v;6!#m*(dFD+M_qN*<`sLVDA7p_1>Hc8mv?M+mt=2#cZ65*(Wq+7nW!-`!U9@A1tZV!^dv(e#DrDtLe8ZoT;G0`ZQuVK-Mxjj#><EXfe3hfPMc+WiN?qYEMZrb$&@Q^{3jT{|eSUo`DStn6=tfW8jjH!ZpN_COB~ZF&ZD6+QW|_ehy2`ysW*%*?%@u`-h2t>0xkfCN+{4q;$K%nhyTas+5q!KkE;%2&FT{Lh?CuM6(|{r{-|WJ#tvX<<O?)uMg*&VgAlxK1dF8<xH<xy2sU=>H9pJt1>lLG8t3XxL>WE#~<&#81E|>?~8(@_6^))sR5rg6`E&F{gTwbPp$vKr`tpBz5nrjPL1VzOSJv}R^>zO|I$8;{V_qpF_WLfVn4<q-#DU(S`DF{We9UKbP_~dlLhl6`LBb}2$>rshdBN~IV7=v-0zJPpIL6pWKdTk?~pU-J9qT+D%D<+Bt2XXv2_s~GM=~n2eN0XO_dEGzR<KiU7>qpKjt%)N|z*8z6Mnj6;M6V0IrDu$P@jra^eK6nz#fnP27Yn9}3X6f}HdHxQ0TUgPbV=?1M&Qa_|J^;y5USm+(FBCfE)MP<ja0aHs*Q)VN%NgR%fpJp!rMe00bs@W%M1Z~r%mc45TQeV=REKR~c+>r%ery>_Pg&C8MByqSI%+{b(NO!0_0@Q6<lk1+=x<5R?A$brZ3sPWuKPs{t#JI&*nM|?u_7@yEQhKHHwN%Zf>v~FQ0>xLXx!G=w1zwttoeN!mrbUT;2?Tx!T!|lGcfnK|Px!vP()!N;4KDW!~b{FV29=EI3?eh50)EDpR+P*syjs{=xkstO%Z+FPv)ftc5y8?+|hqGE0L}R;FENHLMMkCQzky!-bcGbCSU2fuMdrLAD+|Uzi-5m+8ZufPD!=YV)u)VXL%%|yjrqPS{5YM`<hx*(QN;K_2<*5!e9nZaVvd(awF8Ry8qCKIQ{nc1!B4iH+!r>hOT=q`Hljw{_oEnCuXsP*c4uw@a9)UJK*{?4Vjbg|mz4mx0MkdfblHZ`wQ~^|(XbR>cEmHb2K!q;<4br-N0^k{%Gog&x3X7So@DjjcU8jwsyE*zKM_=ar{Fd|cDW~%VqYY+`-o|VV-)6Rkzj5;aFuAdh$&KG-a<Q1n#d)0kO@QZg`C+7W`3SxN=<;`v*5wyCKOZnZd7D@~^R}^g=5?@m=DiEBNY^=ww660H<}>du^JzNFe42j3e40)%pQg_-(^O}ciTRm@xwcdNS=@SOc>$JC+gS-llV7i9=`iyzon=0y%gm4T2LOjIzmBvnzs>yQbNKT){P`UId~WUe+}aD!wvx&V(6&;Sk23!ScbWe}6Z2naVg3toD=g4;_8_h6D9lgcYXA#%9juv!y3S$F_9$ojIVZo%<mPHtw`L#HF}HF$8v$x`ovmzM^ENiGnZs<3akfWUtjzDQSedW0IG8_SaWLOuaVT;!+ae#cEs8MPq8?^jq;R%e%@=VsU&O_~n2Ucg7ysgQ%(i$dvn~EUXZt2+dz`bq&e{Hj+0Jfd^4aS-`MaF_ER$R2GP%XU$+=!(;d+JT0>fsx%&=LmF>G_VelmyKU*N)hCqVA&S)C9e^LKv0IO%U6DsPy=<3IQp?UmNAY5Gls#^<QU3m9MFJn}!J<K^gPBYCZ${4V5gbNuhnZGz)pL}VhzpF@6_ES&QAWh9>D_%!mT@p*^xKfwM)#+xagpCSKee2SFES}<YH7fw@tKK2XDx3G%x7qJHr{S@{0SKMFZ=-ooccOp;LH$lg*V2uxRc<Znxt2q99$e-r;C0Iwz93Myi_xS9f{+D6h)H5D_iu_4#yb+gf=Egrlo{!%*u@*#5|3@@^-Z^SMg+<z5v;;flF@6HckIv&>7ZRNQh+b23v=Vtkt1nO}k7qTEk)}&|+;?z><9~(pILDJ3x=LJYJml;3Wzqi%H<`Cg;^T=}B-q^xU7@acC;>h3?pS9eu@mrR&KZQAk?pd}<8e2%HtDoySqr0=Hf3q|@<v8CH87p!jCME5OkP*V<jqSt|BQCGcsU(Ldt_c-%i*czFt|Ak9PM>69l1e<@QyGtUQb<f9nUP2vleczKH#ZsZEf|kCA2VFZp_l|*5!<DSjKd`NK;2%m%El{++H?!Q;Un6ugS%YG`d)9mS<^Ppo?Dz&n&~*a>hd8fHM(FCcqhtc6Eg!NJOHEkTc#L?nHV=JPyuy2NpvjumdUm+1sT)Rr6T1J&*{%y|1QdduVeY7VC`03Jjt_5DYN42EOtVvh9<-wD3=nQvZKW|D4H1&NkZ%E$h~AQ1cGZ9>RL)ejdL#!mo5D>~5#*tbIP-;ikIc+83MG>AGEk&Il)8t;;#zr#G!$zj2Bj6o+k8smzQkjj1t}c07Atam;JS`wPWU@`mClEyeqk;+S8L_ZqxkRvcycEE`lD<->}jVwK`>AYEm~8|@aL-hy8%j)kbV@KeR{Tng{oilZ8Bs!uD9Md)wQDRs`u%x6lKV8z?3&fl22p)~Go!@C3TZoHH5V3&#3uKvBX63>Y+H?G%n3)Q1%{~YYy!YHSwXRm_NMmA))nnO>ZzE^7O*YR5<ubaa|#>{k_)3Z%bxrt)Y^<<dzUSh*{3Bxt=AwfP|sGfzMQ5?1sJcEUgbL``VllA74^KxwtJ@e%M8&XEt;VF9Le&&P4`+m;E<>cL>YHFPS2O80ENB'

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path)
    parser.add_argument('stamp', type=Path)
    args = parser.parse_args()
    compiled = args.object.read_bytes()
    actual = hashlib.sha256(compiled).hexdigest()
    if actual != INPUT_OBJECT_SHA256:
        raise SystemExit('unexpected SVM compiler object: ' + actual)
    retail = zlib.decompress(base64.b85decode(RETAIL_OBJECT))
    if hashlib.sha256(retail).hexdigest() != OUTPUT_OBJECT_SHA256:
        raise SystemExit('corrupt embedded SVM layout')
    args.object.write_bytes(retail)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()

if __name__ == '__main__':
    main()
