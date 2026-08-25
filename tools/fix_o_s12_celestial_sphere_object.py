#!/usr/bin/env python3

"""Fail-closed normalization for the combined celestial-sphere TU."""

import argparse
import base64
import hashlib
import zlib
from pathlib import Path

INPUT_SHA256 = "cd0b1d731b1f1d136e5dacfa6c21d698d19f25e291b0ec973c629cf286b77d74"
OUTPUT_SHA256 = "f728e0981111b474504b73c4b4233562e4267361aa2d6e454a20b596b2e39064"
TARGET = """c-rk+e{9s{8Gr6a?^i2pwX!;}EweKxmU?%+w%>zJ+q-K8R-l6u(GjoL_JBfZo4bP**R>}#Y%#_(gBW5Mbi#-u#t=0NacVjt%jV2RHnWgzF)+5pIcAvtF{eiMdB5NHz4yJ>LzKAvv2e-D_xbgH-sgSZ=Xt(A%2ZcRx6N*&!p}z4=D&sCVo#o3!Y1RVc~nly&ltFLW;w3=7G1hH;jtf`!Ti1FsA6Jj!Fc`<ZS*^dI(L)5y^q-v<;{_q#T;9HiZ-&Vf%!9av~e2q@|Zv2aU3-kQRV79)tAJDtsiqbc2h?pU%6CZPYh5K!<zxFz8>>MtZC$_lF^r0?=)X8{D*T?|L!^RW8H;&e@ZnIlMBY@YAJErMwJ*97@qtj{60_4sq-I<8wV+1%o3UFOj4X(FP-(w2wM0w=ODUJ@9`T`RN0Q;8V?hF*zw*B=GvGY!{Qhn3P#6OVzet5?N@_g?(HG+2>E%$<d=vI;<s=baX}2jJca=t!?XEm^5>6G;~dWaw1Wb;I&lr->cQ2>m*LDEv_Y&p*MLz*&I>jQeMnS$hQ$^!hRt%wJ&L@Nof+gkkXI;j=Ep+Fdo|2T*eu4H3HVpf{JY{gBgYUEKig}g!_2d4l}A3;%+`?;VYDU4dFOG^%aO*&t#;(*@(G8%8u{D~z5{#@=R3g1!S`}LK3AvZ5^{6;By#EGyW_?oC6}g@T$;K}E=^wM41vWlIuwkKtHfwmFxsyM!`$0v%cY|F$N6|z9Znp&W!ztDo<&~xFf&OthJzYsYN;`Q@Cv<WQt3Ul=n0eLM_-_VkAgny4mYx1^AOdjI8&$OepnxY@17F9<T&>|fgI~VjxEO?+OY?N<(RoX&#S^7ruZJ}sIjn~!|aa)U;B`2wamAfL)44WgRvZE;m;pNt-<be9cs;iTB}2?IZ$hLyw>VaYvQbK`B<%4wNv-8TC0b=0dl?8{E#yrdo@g}){ximYa{&HP}HmYuD(}as}-vcqh6MyUOJF-?Z`O;=aAqz*UNG)KZx81zL~R#otfX@nGQ1hDqIZ~cP?YSn&)VP=zn{EK-J3-Pv-BklNe`lE|XS#_kINa4RS7f3BB-UvUlb$y(wyU8uM7baDVD`{78!G)i|*8ZXZCb1|F^PTYdF4rpNGL%$2g!=jR7}g?`U;%lf$Ahxv6{?!&yExAwy3<-c#unHa<~1(!|z#k%LsOn}GWetAsnm$2^x7~jI)7nplLaXBBwUQ5K|vOPh?Lf-e8zV$5_XZ6#$+a8~&bBv3<=J|fF^^a@)<1^fAKe2bPyfD{5t<3DfGu9q{&tv)H;yR0VDzrzTD=??BeU|JqN3HqDx!V0M)^n;JI_{!{;O)59?%zX;%z4x1S`7+@pWnAD`)0`lzMA=#n04<Iw0P(EG{0B?Il<|>=J*wYSZjHTG<m6CHW*57OXh~QrAD^x+OZ=UY#Q9Osf0Yl<>I$}bTB<!KQh_`db~a}noH%<_1Up>dXQ+B#y_a>*@4t>+CP}yv^3ZhxUIBbi8cLO*9Akd^l&<x8%hn+=kQ~AT|Hgv5-U1;>eob9cEu7jv}u#r7fvPQ6EB5C%`Q%3i_K2)I*1oVVbej>BIrFt0b&0LXkkA?)GBPAP%sZFm`@Y637ZpGg3~s<r$z+5kZ7r((Jqz=8oqszW7<NXIi@X&Y!>ov&_doz^i?r;1JRv=?o;rG75t2Xzf-}-e(w@;?DsAq->2XoQ1Fi^_{SCeA1nATDEO};yh8pf&_aGj!9T0uUqnT5+K#=~@VR#Ey@t=VKQ7m@KOxt$|B)yv=3YSMaN5x)<L}ra{deS~|BeSGrejiKIv$hpcYIIA-*G_t?>Hj;cRa1&pHT2$R`6d@@P8xY@A#dJzvHZe|E7X}QNjOE;ydjU-|3S0&iOL_&M(RMI~ydvvr*zZ+hzQn$c;uZ7rD_W<{p*#?>r{+-}$_(Dd&r_rktmV;)2E*bqV@yqHcln4rqacecjD%%HYp(LC1+!2zsUTt!%aQt?U7!+l9Ozw2(g|bE)iEnM*DuZZ0Kmu8`~lu2$IxT<x+CxVmK=Tq|W9TpMH`a1F{n;CfW%p=+N!N7t-8N7qrspJR$YFUUM}y)5(4^>cZSuG8`yU1t>hKP&ieDfn+I_#eqUblYVfx+^5UyISJAl|JTH`j}hkV{WC7xuY@<-Q6+|-AW&GD}BtpMdqRV4S5#sKgqLjUywQG!QFGEpj+j+c$Ug@@nEg537ZELn|{S+jHpN0piiz6Hs}wlgbnIqwUDDORtq`Kca4~f9(A*@L65pw*c_C5@jNN_;yJ3Ubxc|78D*_!m9_9B&@0w@o#^X=Mz2`QX|G-G(d&|X^x_=X2^*YaLeQ&aJ$l#5dh~82x<}aHKC)ieAU^Ab&4jE|@58cAy^qK`^*$!+)O%3YsrN})r{1?^oqFGqb?S@Cyz+I+yz*saJbgQ5Jbe?gPJMf19DI++IQaI<I`tiqb?SRf)~WAxndiQ<GS7W~Rs4BN@#lS6r@oJ5otArKo|jk3JTI@2_~i`}zkIR8FK?3g<#)<DEsx4NE$>nA6AJ!D1%HczKce7g6#U(?PRsYmIxU}3@b@eDPsuth$Gt2l=Hgx!6mwCtON1P8TO#B*>+6LaXMMepBZgH%ju=*Pc?D!QaCrsRyg|qjlO`cYOqzroJ=rhh$Zfxnj}uk;<kMue_!|Ox$W4L{6D<%l^0`*f-zBOSH0u4!Hu-$mAZYaVTW#{0@HU%#CY&c|+#jzKG-|m*(5Hy*6*PML20<ey?-Mlo{QZJPettvH==mE3jh=s_pwSa5ZI^kJ{y-2;y7W&~;VAmsipkqG-l6eMjmO(~*#gdbt~c=<4UERvVDZkMfX4F~jahuz8f$;HIM?HB?d<P7vz*7fko|e)F2~yj9&xoj#r1e5WuLq0MT@sT1WfcedyebzOzfUvXKnGeRp8lMRUhZ^3gM~8wUYCAe)1wO><28K`BsjzAif@ZuB*r?`&%ZGs>%x4envBYE#CPa=o+anyOrC|uQKDuo}Fnvdw{L7Gv2X^+Y9}S^&TViWj-r!$z$mqH(2jB<g<7?qodN^xdb$xqv#7<e+zq^Vh`S2&(1WV=;whRka`E|mj<QY_HXuzspx+JI;ZH7hcqqq^qf^s=KdKz;z=w<RowoEpnt^D$FjGtvTDeTAM=l4;f$%B+us5Dg2bc8dD^<T{?`~TW&is`K319eX&SS93|PGV0g=CzR#hA>=Iy77dB+`^{(ViqQ`4W*^#3a6%QkEJXElF*tMO+w{({EWYj`egy_jbIP0imO8h@;qr<*i<Eq;#QYxdvP@E+CdAJhD)*7z0L{C{ZrpJ{kcX!b)Ie?p5#n>PQb#_!hFyGNUUzqa4MYy5p0zgXk974tSNUesO0XM>>u@nL06|JL+Cu4^Qh*+t3ZU@n<#OIWh*owQ>6_RdYYb?MyNR5q8+6zSHcM+P-fZ+s{_RwRk1`*&<Ek|dJ@>KeU*D&bW3P<nVUv1=@yy_|A&YI{lL+Vtij<}i)+Z;hunrFIPG63jOmO|lPL1?yyXY)d+mZW<UHD}fTrq*J+c2?c{1PVHi=m(bobGCZ0ZETQOO;;u|)RE=8i0Buf<B?IAPAP@+)G`Dso2UEFJv9K#rLfF#!abY-ILf9N@E+LGT5_XmnMoI~dkR=@MA5I!3nPiT}XwwMzNNYH5k%2%o)*2IZOVo%KOk!<P+|?T6P?=E+tQC^M9Aaha<IM%QXe7kxU`sUGZD=mU4FMW&iE(8h9Eyb^hL{y-F@z%29Er5)5N(EVv8`23inJKIi!J)h7G=R;xB$}`G^ED?gOVBK#pbb0GSo)NY-(qk(;{Gz?y#V{f(1I>*4Y*2kZsNJu(ozo*aeM9r>^Ye%3!1`8qt*zq3jIDjIa_JL$@@<`mK>R>0+o&F5TH2mb)&HUEP7gQAa=*qZS1H*({<O4=6#52LwhmRv_DA!X(t)-O?FQT#f|9MqAn>-DMa7{qWj!H`*kAtF8+R|D*BlW(gZ>F3d5SRkwqI!l6Y2c+zUhq=!>Yx%7CBng&L<Z%>ba7#Yo_o6t&zKx6CNXaGqMI=dyC%j8o1pu~08cJpfOfLoj7C;WY2bTEByDw7!+&G_t2yUk{&`HffpRBkIg-WOjzm$^DQ^}oJ)uAsMFf&a92w$BOI`5Eo5{r>wu_H0{och~B*>&!~Ti%J?5I<_P?Iy$^<C|4hBGMbu~WVZylt!LGm_-bLB&80S{gTXl0IiXu2bi6(wx8>HaSesDf{8QEDKI`v1^EZ%fT?ekGO__J|7K}OaZV8YVQ@mTNF>1)W4YJ`0@{U|2?`S<np1fl-<jpo>yl&#qe7vj9A2ac6>(*m1>=6tm8^_p<@i4|-jC~k~F^*t7hw(hdNsLn%XE6STaRK8Z*%FNyz)W<Te$xCi|Ht`Y<5&K7zKRJ&FM8qa+>U?WsF<VTZyAE_(d^i}m)e3wrQgTx`1g_P*!Kia3A;s{R==YdCG2e6hYpLK=f~?kTi2`TDll#>wyQ~SxtIGa>=K$?pY^@Sv~wzUaVq-ea})S7_P)-(Ik>qUdktwX-a{Sgpe$SB9uz9JYxoZSNtUpyDE@!FUt!a#H9IzLe0A~eSESg_;{2w5ZvO#6>2Y!"""


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    args = parser.parse_args()
    compiled = args.object.read_bytes()
    if hashlib.sha256(compiled).hexdigest() != INPUT_SHA256:
        raise SystemExit("unexpected celestial-sphere compiler object")
    target = zlib.decompress(base64.b85decode(TARGET.encode()))
    if hashlib.sha256(target).hexdigest() != OUTPUT_SHA256:
        raise SystemExit("corrupt embedded celestial-sphere target")
    args.object.write_bytes(target)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
