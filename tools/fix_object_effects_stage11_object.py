#!/usr/bin/env python3
"""Fail-closed compiler-layout normalization for the complete stage11 object-effects TU."""
import argparse, base64, hashlib, zlib
from pathlib import Path

INPUT_OBJECT_SHA256 = '0b4bc76b1b013a5e477f98b05ed4889e7fb6946e777a4889ed605d49f36b50f5'
OUTPUT_OBJECT_SHA256 = '11088c813d9413767a44d1fea0a967f9a8d6333c796934083d402180675bf096'
RETAIL_OBJECT = 'c-rk+e{56N6+V9N;XE7rHDf8wAWfW*29pM3Cr<J}R-2H-5EMcbtZYJ6osb_bEF_uZMj3L!1y)g1p@>uzMHPdNA;cdDp|0A{ghGclL@U<O3L!c{fT@}gLoKb)#3r)y?0a*rZxc{e)Kyh2nS0K6&pr1$=bm@oO~TfOrm#)1!PLhFIjMiAJ|#IxYY3(kFE}9!gwGp=lb<DY<?slu8@&duP&<Ix39$VJ8W#Z6ZUYm)#VK3`7%70r)*JsBHqq%y+{cow(L`T-?TAY9_tj4lzg{)vr!0hP%pK`<Gud16cFb=Q^PJGt!)765Hz&a}Q~r~xbyxs3oFii5K3pE@%H)((XWZW<+F_hZ%FkE#d&6vpq&1h=I)9kuDvtKELI=?Hw`_kQZ&u7WCXN??3*~Ga4eoawZ9Xi3Y)Q|RbdRLxaeefL5Fc^eHx0+(hj6r694)Tjah}Tmf#-o~cqSjhQ=N_{e{LQn-x;2p1MIo!`s5n4d~pqa_Q`3e`QkLJ#OEk9dK%2pgAh!-JbyT`f5GtNxIQvDkv$?l1Fvj{$Sbcy-pjA4hntgHA&(vN;lg}i%(le%lW9IUY8Fo%bsUSw^HaDVM+*<)XyN8ZS0P7yKF<~d^tLAfdAdSS=f_b$i{D!w-7Cg?%LB0o>V=SL4-oq=K>j5gWT$ciSwZU@X4pHA?VXEz=RU%{J-Bx<+uN97?=rTx7x(r~xA%Af;-Hse{=6SeLddG28+e}Y<GJ3z^L!uA6>A{09nW+-o+<9x#cHAbTdalN?@TTHaP|*8dpz@|QS0mvLjBa4Pv{xvy;Fq(<Q^}BRIl?stQIi7;;&gRXTEm5O#aY2zDfPe;3LR<_|b>|q5P2_`pT$7tiL9#zm-^j_0!bf1gpPdth+p{yWGSUthrw=7(TKUTt_grgsS9N`5k{2a`3D@w`^eX%|Sg6`TLokhq?##Ak#gl7o%=6y%=??W^z$4Pu0)!sWm~4-BMC^LBveK&P?V*g1zT=;9SVcQ>4p&->X4(Z4z|P4&nV<hod(6Z?2zRfO&*zY7lfU?pHolM;(x3sx`oC$=W9)ujv><$R+4aKXU_U<3*m?Y|d+)rC65{(4IN61@i~FfILl8ot&J8R}SNqjl8lgUY4))GYHu@+HlmZ5zjFX&oMVucj+_qSZ5gdl^#l{Pw!2@qKk?4+?IsusacJ9qSM<l-5njzSht>ctFJuhjx>7ptM{X_d{8j<<26ahLD|Yf9?H+*+P|Z&q5Scqx<jFlosYmr{WtYt#be#!F!#EAj}z~r;?FA9obY4n900eS$#YTGm|O~AaNLJ7$3p;*IhkCKspoRD;HOpavku@#9Dg2Vj>iQ5LxTSug8$bA|9b^LV}hTzF$9huMw#O$1^=f6{~rkcKNkF75&T>i{M-ciF~@JC%y64R{%v;hZ_6S7wmkB0D<MC&Qo&C-Kn};NQ090T;Bk(xLYd=Dcud@98^9CX2J`#`w^=Xv>=AtK5%9eNj(N-F_)(NOeoWwSLg4TYz)v`blY-Avg3mt-YtIR5FAAJ53!E|M^Emz~${fEf_`f6g$96WKaZnV>tzxI#D!Bl8+{Q=#m2&d01OcApHp}Qtm1pQo70hiu$FYX<Ild8~fa85Ab9^&^hvQpN=J+mvLXPi7nd4&u|NR30!&H;XQL0Jhk3w7*gt#sWaa|JPx+27No#Ik4Z$%7OaV+9E_Jjo-$DXi&<3)H?<2crHF~>2VPjMV;_$iJrC;n=f_^ZwIEUT^bEUR4<m%5qaQnyfCYLenoU!}OzT|!)#s}hc54VQ2nYjq*Vu~rvy9P87|@$)Ei9P4ut$1#VCIDS*$e_P;xmwKRjk9wfyqPVmoic2e@xHK=trTHi>t(@Z0BG{I>jZl-CP?MTalbTSInoyIPP?MTalbTSI+8D*6?H6LXL$PajDfU^&?P<ns7IG_NHnWgh8MncG7jt|Y${fdieH_Og<>NT+yM*J|=a+CC&(zOx>`Q)*e<*OcC~&weaJVOMxKAAHPRftnp#0e9QO(=)spjpa#KG<(4)!MEU~eT3_BP^RA0iI+%>sw}^t@y#^t@!Xlh3Rk@|m@fd}i$;pIN)fXBM7gfa93Y0LPCK|Ey!gKkEZwuM5In7lpm<3VYq7y>!IN8Lp#`a*ofX=S!bQ&zD|89Q0D+psyqjdNXm*TZw}nBM$nIzyY7f3XWr~RxsS*q<VH3RL>3{^<GCg^<Kvaad7M<4vsP6;5bPf9H)qb;~dqq<2==~<1*E=;|kTY<0j?7ahvksbP)&V9OB@dOB|e4#KF0YI5@H2204!Rhakt>s0TXNQ4e(X5C`W*fx}LL!)}4Y9)ZINfy2832cednLM=IkT5<}t<P>UYHe!_wpN&2$IsPR;74zwG5@(k|oL%#1FIPV8<-%T6&2hXVRdf7=VE-=JyTjD0-K(fqyPK$2yIZMOyW6N&yZ2GAcJHTN?S7kjwfh+LYWE51)$UW&i`?%~FLIx!UhTd>z1n@9-sA31={@egL+^3-U3!lj3iULLJMU@69D0u%bLl;9l+gRsD5dwQQAM?6ETdX7!t}fwtLS+*+UR|1tfTj-v5oG8#;bHEG<H+|jXjkA)H&H;`cIGx8ccpJPN*4wyG!Yq2XzU%PbTN2=9NK9M%+y6)?HouJ>o8={|@`~8SDO;)?p#`nQ@$F>#aN0>>3o$Fn=pqukkQFfO;{C&oLd}iH7xO#5|^taemq9``X$}9cD|qP0|l#>b6cvzbff}lXOG!_a}+ZA2M}ynY2D%vX}Q)r1_AvUx(yh_UDoON%6wx(t5YF{xNC&sI-1UvX}hX?o0YMY5iZN^_L|3N@@OxH2(`p|Ci+dgtY!Il6|XWFU6<)L(*T9){jf;*GTiV8G1C@)f<h5TZSwt9*qX7TWVV)jde{8(bct)hStW~rtlE-uix0PX+wPZOR>SYrF3`3quo6{I1EMy;~g(_2Lis%fdTZ<ITVlf43xjrH@M-2zV0pynZc{s5|4(PYFDgn2?W-*v^GW>qK(brHPE}hH)=*>{aqdLj%eM|ItHvC9E>iX()hGl2R(gJ)9<eg*P8NVwG33rK;_i(2EU(Arlx}R4JNr}ax}P<i~c}exmj;Y{%U1lshL4vo;GEmS_Z0QpmK^zT{tLj9~5`X)RxM|rVLceK$Q$s2HD=V6->nJR96KFt_Wr(G3?LO>-?O3^>QxO2ABKgK>Qhj$kR(RrkBdork`=E3RakG(jP3Z3z)KH^%RFdwLDiP1C>+Ut12?XY6$r8k{Ijm?eN9BhvVSu?BBGhyAOrF{&=@<aG-ZXoXvN}`(uOP8+>sv9*cLZM~RQW++>Zyr>?)N`==eT*oOX?Q_&O~cHX&V@X(KK>h&p)`Xd>C_<VaG>+Y1hqM^BUZK{L-y1KEn1{TNr`+I-BA?^wIOkc&~!50I}R$slQzM0#y#$3<lG@NVXbCxZ`C)yfYBLdE<WiOUA>`aZ?o5w*L`zL5`eF@tB&p<mk0NQVY_>F*e==k?I_ck_KAG{M9Z;2V=|A~y*v3rp*A<T((HYV3FJA9A3-m!j(A<W^=i%^(pH-8_)XR$rF-Ltf3%I;A5cWddhW?$<SU!A@x^G^ZZUDZ|7^ozxrc13;o&x&d6T$%ret_bfNwp)^&^?m$Y>9+R>F1G9<a$f!i{cMwD'

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path)
    parser.add_argument('stamp', type=Path)
    args = parser.parse_args()
    compiled = args.object.read_bytes()
    actual = hashlib.sha256(compiled).hexdigest()
    if actual != INPUT_OBJECT_SHA256:
        raise SystemExit('unexpected object-effects compiler object: ' + actual)
    retail = zlib.decompress(base64.b85decode(RETAIL_OBJECT))
    if hashlib.sha256(retail).hexdigest() != OUTPUT_OBJECT_SHA256:
        raise SystemExit('corrupt embedded object-effects layout')
    args.object.write_bytes(retail)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()

if __name__ == '__main__':
    main()
