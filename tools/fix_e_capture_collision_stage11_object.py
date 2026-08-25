#!/usr/bin/env python3

"""Fail-closed normalization for the stage11 e_capture_collision.cpp object."""

import argparse
import base64
import hashlib
import zlib
from pathlib import Path

INPUT_SHA256 = "1871f8351dd8f431c6226e46af40d5f66b82df160b79f74feacaa7f116d37aaa"
OUTPUT_SHA256 = "bc854eb1a7dc5856e275f9805e09587fc21835a3c1c55cccf6b48711d59d744b"
TARGET = """c-qxjT}&L;6+W{w;KioNVlOsw2n(^35PMB`%>qM9Q<hz*kuXLWH*p(jSzv6|U0Afcws1>e4XKs1en3hdtjLm4k|IA?iB(lq6-5<wTuaSEg_=11QGZfJjiM+@-8gD3H7fn?%)Rrs(?qKL;EZ&9zw@1Q&pqeNo!L8hp?9E9@=0V~5(V{t&1*-v#D<uzG}Aq_g>08PzA<zF<8w_LH|PAm)n&|o_ODbuw{YL=@<j@&uq}ruaAt|<%sC1^`HZ|eSW=q8GEsby8W-OE_iX7RDe4OOxKBX%*ld#920jp0^cdBp1qvbuX$k9=u>PE1UR9eYFj%6-E+nr$MYOh?Xnhy?Aqs@yAf(!~Bi6c10dRFLt{z+?i{(|Lx<JirZB|eBBI>p2EH`zOB<OyO<dxt59hZ1q^fyd87hDOEf@P!;QXahm?6qELiJEy`5sV7P7)C!vmDx%PRWHlbg)xA!8)Fb-($Py}zRKpZIQl(?5A$bpy=r>)7v!Itzi)Q#;;z}|20h=Qu2HssFn6BnRGGrd4HQ=AsaeH3tk#9sZ_S$colP-TXZIQ0A3m=HS-5s<R`{}dm#~hzX0QITIija#9t%8=5QWV(WPSe<YCM3RHVA$V{CWsI2%!fd-h&W&5JC?^=pSNpp9n^U`C;_4In0K*)w&<{9GinN$mX*>?{(k2`f2Y2`gDNR!g|d6dwJn6w`RpXD?MfO@vf}-GwxmKB?_0mPh`(+4*RdWM1IuKSjL~xdH>vtduR1JDu~2$=G8~f9*&}i#xr$!E+l^;dg!%h*t4Ur`#RP*3%|4c*<ra=a+`q_8}{39HRc4m@NQmSHRdDVhVzw(O{86^q<V}B#)k7}sY#!=q_4Hx7Nfb@cuxmLSI7@N$Z{K5*>p-^x&znO*FIY}t}nd|c?EJsFoQ=9_Vf-roHj-djh#rOXNo8DS|XRtW(t|y^qt5t5g!^kGThskI5aTOf4Kk9Ah?WWMwgm5bNn>XBLcrbw5O8eRbYkVt3-PRe;ruxZ{rt1@P7d2yo7Ndk163dzD3|CY<$+ne}vzD9!L5Zn8)!wO7sBdeLcW}f1K#ce6DYTC?fDFqNwoyF0k;&)3jgs{EVnoVBEQwz}IbSy<uAmbu|h8&%lEJ*vi@WPb+76-pWB<v~rNo5w-EPWc0aR_@K}2!soJ;oBR_iH~Cd7H~HsQZt}0K+~nU_xykQYxyc_`xhW@z?&rLMeRjX#k!OS8&jJhns#S|}-Ks@dw`x(|vuaU3uxe3mTD2&*ty+}-ShZC6tXe9zTD4Scw`!@_W7Sg8V%1WC9zHC1^zdQ9|Cnf(;C~7%c=RnOc+?dXJnr>2!K0ts1dqL4D|qaITFzJAL-Zi$E0Obqg5OD0FL?Ya)+^TIwq2ZY{X{zj#t|bVFkWr<3fx6hEpRtchrmgqEdt{wK^1s_s8iq}qOS-%LiAOE@w{{ijOXQR0#6ccmHx*o<X!7!vGEVPL3W(kb=~LEWtXnFbo^5KYDG`B>ha{wMt|tMq5C?3S6F>q|0VE;tS&>Ba8IOemL8w~BMj&fWw}54E3tQP7uWF&No;<Y>l=_d=;!$SC!xOt{TkQzLC_z%&Hd3^cI2f4eEoLlm#p=rgMgQ9IxCy4|DmB1_F2URjF)&k(WAy1qosdi7*cKMz6<=gE%YC9|4lV|Kc$llvlnKKPw($5ynl*e_kG0X+H|}RDPZZ+uYlS2S1s4^zM)6h?J?rX;<zv7{|Pw4`pNxwvR*^Ba{VIkJbM}Pe4c}pbltH30C<r-9Ncd1{Th8g$ln(GBVfE!Uv}zpzsv6Om!Ed&$DF$KFW3AYr%pRu_H|dhT9^O#T>gzN|0b7x%4N^H;yvcln_YUwRnM5qo^-{3-l31X4jH}E#r$bXr6!80R0lhSXye7cQ`A2-6+c!ytQCjTg`$>s*oL*~2^Te#%oJuEOi~*=dECLIQseeDh6E~0sV}2tCq_=sXa#T6V0y~KG^`!ZuvAG)aZ_qs*iwaJ`nVR2wv5lrlub<JwRBM{qgh4S^l7$OneE7QHkY0#qX!t-o6qO$%^4b}<LQ}HB$kRqBGI<a-oDgCx|nv5@%FeE+3rC`qXwBB%cfKvrVz9*LC2<{cP3+ihAp2ntQ|?i7>Ts?s6A!Y9&>7IkLB3gZqjWQjI||bqKNWzpJc0PP@`pWBb<rE_9vo3u@Y8YM6c=&0LI8B-Wu&u&1~W(jKx*k5;0fAc+|Z_U(5`WG+}EZ#+QkzopB4tTTPda{V{jwSXs5gI}z`Tm|g5NaBC_W@9c?)c<t>G_w=Y~j7Ln^21qS=Et_sBYO_UZ8P82kY107HxuVvB?U?}{D-^iXIPMH^VX{!n7t>=vVmv*ikH&J`TZi7?47myIv2;G4$>lfu6rUvdXnXkcKQ$!lo5FMSyGDhhyLFWAke~E9`WNwH=i9n(^bQUm);A#zlNvVX%)VkSm;Fwr*cfe5TUz%OCZpWffACOpQ26qfagy5<*!qQy?+?b`{$~I1h>bU{syAOl3-KGf<290wzK=9!bgt^nYgF~t6Oc=gPpRq#d~akS&~Lm&Rd0_{)o*uG)$i&d6Oc&=?7x3pk3~EF2zg(RDINVg<R;`3$Zg1{Bz>y}5`@%2Mj*!^laLd74tK{rk@(2J87h<H_}162z1)wV)hk!Xc`jG1?+J(Bn(=*7=696)@pJ4Z{<j4461%*KWBWIO>ftBx*xfuHV#(}$S!J`a^Xx-Tzs;X;zKZ88{6?I9`hO){;C_nDFG-H?mo4y--(i7yQ3^jobvbLecMj?mkN4nyr{6aA3Qc+VRXhLhV;k;=uioXyr1p(Hi&rhWcFp+PiSvH^7b|O)8~"""


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("stamp", type=Path)
    args = parser.parse_args()
    compiled = args.object.read_bytes()
    if hashlib.sha256(compiled).hexdigest() != INPUT_SHA256:
        raise SystemExit("unexpected stage11 e_capture_collision compiler object")
    target = zlib.decompress(base64.b85decode(TARGET.encode()))
    if hashlib.sha256(target).hexdigest() != OUTPUT_SHA256:
        raise SystemExit("corrupt embedded stage11 e_capture_collision target")
    args.object.write_bytes(target)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()


if __name__ == "__main__":
    main()
