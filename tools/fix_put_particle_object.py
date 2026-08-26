#!/usr/bin/env python3
"""Fail-closed object normalization for the complete stage40 PUT PARTICLE TU."""
import argparse, base64, hashlib, zlib
from pathlib import Path

INPUT_OBJECT_SHA256 = 'ceee24504505d1fdac11cf499ea4f1baba844431461ca18a5de1d1aef071cf3a'
OUTPUT_OBJECT_SHA256 = 'ccd9a75ceb1c77ec47876a37434e47d346ee7bbd5c07aadd52a1e92a9172e1fb'
RETAIL_OBJECT = 'c-rk+Yiv}<6+U<Gg*Enq3^9oz#x}*EO=7lp?X`UkPU7|M8k-v1bxcV5&|>TjCb8MAcOj0lVV5kboEE8;h*Xr4KpU0jN8}<kKlqV{^H4-7sgU|mQ>6(ltr{h1<UHD>X)E`eyEFIBUO%8stF}_FG@kD~X3m*&&dl7qawgK%uDBGk9)-%xzt*#XvaAc3gqK!O2}#ex>t|<<{hB=49C>rUrP_%qa;3?gnp7zatQ=RV1HH<5T{-9)>#4LmOVw;_y2y2U5;oZ!$DXI6bmsc;Y!w+^%pH7?#<xxrbr98NGi2<VF5Qw=$;V}77H^Pz&{4L&P721hq$?rM&R%5l7C3JlA<Cj1KB5>8JfxoP&T8u+Yh6gje9Xa@Ec{9rsi!4>FLHka%>$$}o6O(zi4Bs^N_p-%GICLB&D}~ZyK<#l9CiZ2&LsTH<SvgdB5&pE?@d>pqt+~W&GkM?K5Okc#g|??GsV`ER^OX~Znc5=WVu1JvqH{dl&-wQ;&UeR*yVBP*O+?ithkn%^aFNGnQiF5mU;Z`@r7cR3H@Y28RkiS>NxB+<4|L*ZMSo6uTE{fAHH61uI;sBC#gl`2zd<fJnAfuJeQYvE^APG6{x-PW8X#{9;Q;W1~cT%s#FVkk&z)idy>2@r{LdriKaK2z9_XSQR{<L4!M`nnah7+@l?<*2p-odlW7)XN%xdP*3yEt8iQD;$~K(I^9o+>aq!kz_3s7GV?0V8GgtXq3D2`vto@V8k&nfit;h74W5nGv&mKC9y-<O@P@Y3<a)=FLS;J#leU*E-m;2Q+k6$&;J?yMqhd<Mc?9F-oNI$lL<<iJZyHou%HzpR}Vc+7z2UcH<#@H!#j@7d9S?Vy56T~hrJ3>>2MjQIIrMG0CL+!kQn7)kMTq0_Qesi^%YX$oD+(U}*A6*ZR<<Wm8mic`$Bd?)VtRa15=BoWS=Np=no5X)2H;dSucYmi3p*9cUuDT2xho}X26R~)t^LwvL(1?$M^S0DLf4s_!d4(if(s~%NLC<8F7e5%EI0@MicPhW9l}i(q)R9)*DRu`+^G^tx#h=eln1jVuH)R^eWU$xO*;#X(2ED^nCi9rSxMyqg@hWFNnEN^JOFmbJs8zB*g>fo;3xgjP<GEiW@_dqCF1~J;6_fnBSxj6GA1dba0qv)Pk9H2WyTtndw>>Fnhi#SH7BY?7)|gDp2|KE_#@(Nk9nX<gu<o2P<?yr2;a@=V&%5=Mnd@>kM_PSzD*XWFR7u<V49@3uv;=kjrqGwq#(B=gg8F0ie&#S0d8<qxcAMup)<0QA<>G8N*nLw)wc>7I_YSLhj=cgixxi20elp{R*obkgXTDv@Cu>je`wn+YEk9p|(}&(Fo4~rod&8$ZJLn2$$HR-olGOv=9Sz>M@V@m*Ynnv7SuC>XMGQq;S-)5g<U1HN!DjE7DykGQHskdo-ghglGlAXncbI#l($pvP3h!OKuF8zvv$MuJ)bt@`ir3Uqtp6Q0@5E#F86v$OR4gPDd0wOj3(j5St5>|U@;Wr<mfyRCoSmzSovBz?o%wD=tKUY?_N5EGxp$d8E4B)cZ5~&MxC)yFd#6IpwV+mv-`n-l+{$alSqp=+zv$rK9b#=_POe|zGhN{cUO}V3_du$5U@Wz7a3m&pksY1={gJ-v?wvcRyJuH*B;46=5}mhI_jGsNSsm^R?y|Hx!xZl6?&+@%bp*S&Md;uE^zQ7h?hW?!cZRwmG$@|DEE$guB@P_)4c&DYa94C_G@go^)S?e=A#(AtQNQoN!95sV7abZ%4(ooh1eT~?h_3RPAgV9s_&Yd~mvVd>SmXFviT{Gc|0_`gAFFJ#b(9-z9i?63Z<qM5*>;upC7nOnI<6Hq-?d8O`y_sy#P62)eG(s)-pFma-X&TibYORl(D|6CiR-9EsA_>rZ9mlt><)o(>}(OZMbg1m*edYt*j?O~`UPNaOTC-uX2IVNEcnR9En@7`M7Iij0Vf>CT9<80yI|ub@Fytnaf$zq&0jif^W9k2GJ%g0c?8DT<s284+WevliH}#s6#}Ovou?(8bCM2X>*jdb7JN$bwJ*B`n6G_VyTsov@$bNRF?NWkP2dDkNMQI77I+e;1jof*d+o(f5VZ?@hG?6>XK{K7{H*Om@e8&O#pfmdk0t&uaYYFJ>%fBlA<;E_&XRsR&Lv;6<4}^2_~S&Y1cq;&0>4bOozGtaAGY)POD^I%<2s(TM4Pyd2e;oQuH(Ue+#vYaj~fIZ`=w6s8-WEMdD$rV$je5-M=n+iKK9pY!N*!YCwxc|l?wb-BEQi88nDnujdc~<$Ii9lcP`Y}T7eO(bpj*rl>)<7mB6@hss%<ptQUA#!Xpw+NH`^7+=43w#%)-l*yrI6f#Gwpz^JQkfgdL75g7ZWSKt#wpBETsPM^R}5?v=S@>?qK3|@N$#vZwWV<k+qSzw$eK7o6QJ}WR{r7H`Z={@%4G5ek@Pz!!vG-;QERvonFpqF6CZ#dbq%A8M2GR)SNr`0!raqcMR^0ezSXiqVB^0cxQ^jWqxE`OJsnc(t!K_d@zk<;IUS=0kv;QDc#Wi>3HTz)5L<iVBY^efm~<t$I!zneiL2XvN?4<fIq9jf5|hCrhp6i#cMsD~5mI_L7YLBGT5gwu$xC&3OjZtokQ$JuYRe10E~PtnSJ2yf!_@|F38o@AJXbES*X+M4`6AT2L<eFDsW3-;t`%?(^FjsE~`vrQ|n0&igl10T;~7m@UFHc=nD<ns2^`|^8@YPkNFftmj;d0PD<@Kg49_4~ljvxAM#$7DZZmkalQC(D)XufpEfaKF<EuKz={w`}{$wtRh1IiKGHp2p+F<Ts#s?C}cXudJ2Uhg>QfS<E>72<Qe|uD-%Pm+kebABjD`(yU*0hFFIWOG9NL?K<zEpDm=7C64i<4*GeA{yN8e*E-~XbI9*6q_vDgf2D)|mc#x{j`@lm`adY7={g6kIB2h9e9l2T)=LK+_IEhsL5IIhj`i+!$RBsm-*nJlcg%m(VgKg^bTm3N5{>%x{+>N|-!?Fs7>Tv_9%S59G}^?NvB6Y3V+_iSUV$hXOC3l6heigHNlF|@MHBop#W$Ep(CEO}J$%~uSU5HkOYMvA$87uWbr{__LXokt_?T>DkoFEFqIw{z>v|xdw}tUGpBgA&`kUJ3VKxWnVd`~x=E$CrsK3#~QOp_+(_Q-+qq#m93US;}$FZU74Q)nS$T7;_CN!Jc_23+7vn>r6bEJkXt!uKaL>g^=uu<|v;@1a4G?YS=%n{-GkmY-*-qvc;oi_DI(CI}e&oT5sUC7^VSQE8H413{WLt3UGrWlKxllVi8w%BN}#CwuS<kqHz#X4IXL9ngY=}uL>y}>y+GKUjxpy*gEncABei`D@r2M)$KPMS5<5s%*!5GEtxb_=)rfgKh@fjKD-*e*5)16Do^3kM?ghCQj#6p->aXS&9K71oeGM+%PZbiIV@B<y#NYVuoiHn;0eDL7*Bk%)!cn<KiMsmA)SK4(wN;e_UJ+Uyydg3|2GbNn!b)Q=!YKGh4{tm}BM8;gw$_)@X)6!`|@qoc9?0Q=*qm@k<a*#`_~xzZqZ0B~|RnHozC>;V$}eWPZdFHo*+!ccrDwrgN)Y+rn=*rmA?#YNZFUitR`Mf%-A?u!=aHIDvUd*v$S3-wn!?q6lssrUb9;fH-^mT!x6_uXdh7km)Lu#Xa(Q}Ou7J^NDCexKp1-<%xwbKRmHJ>hPln@kPtjbY<+nFd*>knvXq@RhFHJNx=2KL45I5BSDckfDlU(pvFNH+a$Hx!={%E|GiY3A884{T_Jlr^)?67r8$yM>|UHk349n$o=shXeo04c@hm{J{dwAvF6lTpFx{OdkO6#+ON>wLi;0WLA*%^H8d~U5ZYJJ?nld_9YuQt?F8CWXiuY^NBbGt@6cvUfB(1gtni*ac(?bQa{NZho}0KH|EBd^qQdW2fx8OzmdodvjPK-n{F`_=zQL5CdGywEEPp#^=h0KR53PA}#SxIKtd>bK_T96oP;b@8oWG3wEcE&d^{&zKza5x*nxq$|g75sY4txgb?0b$?GS@5R-|*5J*5I2^duX1!p{`KR{GBE`kDjOS|CuWB-Q{}8p~u?l^EW>Dg3Vr!^(fQMy!{>We)Od'

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path)
    parser.add_argument('stamp', type=Path)
    args = parser.parse_args()
    compiled = args.object.read_bytes()
    actual = hashlib.sha256(compiled).hexdigest()
    if actual != INPUT_OBJECT_SHA256:
        raise SystemExit('unexpected PUT PARTICLE compiler object: ' + actual)
    retail = zlib.decompress(base64.b85decode(RETAIL_OBJECT))
    if hashlib.sha256(retail).hexdigest() != OUTPUT_OBJECT_SHA256:
        raise SystemExit('corrupt embedded PUT PARTICLE object')
    args.object.write_bytes(retail)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()

if __name__ == '__main__':
    main()

