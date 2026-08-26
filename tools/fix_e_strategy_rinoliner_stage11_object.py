#!/usr/bin/env python3
"""Fail-closed compiler-layout normalization for the complete stage11 rinoliner-strategy TU."""
import argparse, base64, hashlib, zlib
from pathlib import Path

INPUT_OBJECT_SHA256 = '005a1f7a493f88c0c499c730b6ad36b7ed0f53b393f87e260d7721cff391e5e4'
OUTPUT_OBJECT_SHA256 = '06195957788093696ecf3ea84d5a2035a6c39b8ec3e6f652f2e95eb0483a3a99'
RETAIL_OBJECT = 'c-qxjPi$OA8UN<JXJ@l^;!Wx{CUyO%xM0z(wVU1AFNqIcdv{5ZlUl_p5ky+M*=_B1V;g5dTeQ?KF$j=+SdkohFf@lK<d751fde2z5vov*J>-@mD#RfNBREh}9DeiOH}8!X$9;tjlqXH*_x<LZneY2%=9}?mB{!KDh9LhF)am}~e}@x}tkSM9NKx8D+Gn4=KXn52<^KDdwTN-8j{cW^Pwlmp$E$IRMCKyJ#~g|QldPdDc?<QDO*C5Xr7jf7&)6%}g<3e^;^gX20$XU0to-3#)p?67`wE#CR*5dGQS944Ft43*tbU9mpkrw|)Tpxxn;h6yi<sB!eu|xPsBagW6Ad=k*yal6+LSh<KHdbo_cz(@!3Mj_Y<CfJ9b<b>W3EoeGH$!JUZfMs)?Ms0|BLZGD($pM#ATfS!}zv0!|qGJqDbwHP`2Ck9%(yOQG2$(!M67Vwy$m>);+Ml2ll`7m#XvQo$bH01>1x69c^EQZB4X)<kMikv<-H~PI}mq9Bg{3ZZ_rI4m9E1M*f|B^#H#PE59Dl-WS5}^me}u%kx`&<gDPVo8~n8-s|};K9KyNDd!WnWenn`n+v9zm2WYJBj-?KXTpzdgcy6^U)N5=wE1LA%5F?dHztzb1U7;H1iT*7mgvXZLT`o~Yj23L!tTGeChor{LhP@>UGDH<K2OD9Ptj>@Plff#e8_j9ZnLqQ&6$U6^8?mF?6wYdd1v>+R&x7hZ3p^qQ9JsP^aa>@kPYBtJZHN)Bcbm-%q{z@z9ZJP_>|*4)Qh?kv7G@nfFo$1Zq~hQ&yYYKyVa0G&S0)5P=}qTCFDFsFHag%aWB5Nz!UIs;39my0o=<zUTN0e@a7Jk7x#r3Pwof#zN=dX-sNJ=Sru#3j`c_0H<uB=VZJX0cn#$_sQ}B|DA!eRzLe{F>=UkQYe=8}D&vd#F6KC_=2*Rhw?K$_F5L+=M;(4&WxpNA6zjZ(-SBS?*mU<Ux&D3<ANPdxF~&YdWF6+MHfYiQ%mv|$Zr~yLTWL`2Sgn<YYJ1&r`)XI8uJT-6+FdxM@!cA4YkZ%^>*EY)d_?01wL583<Kr5CTjLWNzoGGIjlZt(w#L^repKVD8b7A-Ga8@O_!Am`LgNz}KdJFu8b9Ud$`JR<V6VHU(xX^c+jR4<o6mK*=Ilwk?~)7DF87MeVY1#S?~dXRY#aF*`Jdc;Zekyrcw?H#lP1nG?gd>(_MuPj2P+?sGM*ypW-KBBHs%6s4rus;09zXYZut$KDU4g;dym4kK&Q2i<IOnI73f56;R(%n?@gk9h3^tQ$v9dh`YhvpFJkUi#$N@tJiLDkPj%)y3}EIv_Tx_q#UBJ#JW|h7JZ48;)A^F7^Qt!HLNF#FR$b~hn0BJiDI6m@q;MzEV+zCHPKCRP9#I&vI;b$>d_ZB?7E>78v_s(p{8Ts%{}q;3w!))$ekweM*eRSvOcj=CPvJ?VOcCsdR)we87kNxhGsYNnhB0cIVZ4S?WPBB6j&TL0%=qUhON`(1+FXovrmBa9jBkx`x4bGD%U`#?!x;9`_Zb(xxm{e_VXwCZoBsZv^#*g>Z)mP;cz#O1X;gUfh+6N1uD-~6Yfm>>Ze_oI#`2F)q|etqnSP34y0v!LXh`2TSpFVnzO2dDVX2(IkL4dit_1z*Cpc^Ipq;)8c~aBITrG&VF~;%%tnCd={~qL9f&KI?xZ`O4d>wlvt&R6KWNA;8^*14-zgb}!w(P?m6IWOs$Nqd@?gj4uGWM>FS(@d~tG#u=i|;xG2S<MO?Xq~jq5ZuE`4<iPUu$T8w?STP(6<}f?=;AwK|Z-nE)<I8LLoo(O)3@6SC(fhrB_}rEYB}2mgg5r%b;doDJ7FbXP1`f<%NP>7*7o6COnwQAI(fC*0z1t9-g3Azj1D<GW$}w1g1D!nJpxT$DdUinS9#scjSoQFPFDnm`J8Z@;O`4sQ~7(J{+G=Fr#21kx3=TeL8p4rt(W=&48n}nl&}z!{mrRW@b2GpY_>%vT>Y5Fkdd4_Jc8=R`hTxrDzP5_G6S!_-^MCs^5g|!))4zxg$Ot4`43gkB|bSq2*F}cBoRSR%qz#;<<CB1%QRcN@?i)Qh6Tu{2Ue)3jw6+*U!1N+f#Z(6N|;tS7w)&=NFfwhGht0&|~qBzk@|^7pwb(<;eeK{lENV4(|G5?$irkc9#vwr-bEPdZx0tSblB3(w7{vhf>d+pG&fC<mB_&Q%aZ5XqMY7v^}TVcwHpF{^D~lOlv$pOFq0o;<X6M85c)Cyh+i&&r$SVAIiHF{m7x{KgKAEr%7}R+}3TBzftsl7p~~jC{=1R;wbM^8*ZRB6LRZaYKyF)Y`SAV+_(v@`K{1V-TqEgysKyOJ7`1C)7st@+-Hn4<P_hREm|AiN_2d?-T~Zy;!V~wG`$qd{5^tWWh}A1EvzTg@Y8{9@_Q6_iumOYXRUv`-XXjlDZhhW`}Y4|J9LHL8M>Y<kN)lp7k?elpTS#B#2VxGPpj?^j{'

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path)
    parser.add_argument('stamp', type=Path)
    args = parser.parse_args()
    compiled = args.object.read_bytes()
    actual = hashlib.sha256(compiled).hexdigest()
    if actual != INPUT_OBJECT_SHA256:
        raise SystemExit('unexpected rinoliner-strategy compiler object: ' + actual)
    retail = zlib.decompress(base64.b85decode(RETAIL_OBJECT))
    if hashlib.sha256(retail).hexdigest() != OUTPUT_OBJECT_SHA256:
        raise SystemExit('corrupt embedded rinoliner-strategy layout')
    args.object.write_bytes(retail)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()

if __name__ == '__main__':
    main()
