#!/usr/bin/env python3
"""Fail-closed compiler-layout normalization for the complete CRI RNARES TU."""
import argparse, base64, hashlib, zlib
from pathlib import Path

INPUT_OBJECT_SHA256 = 'd6afbd6e1802f48e861d0baa963422a8579032aaee677294249a5966bc522b4e'
OUTPUT_OBJECT_SHA256 = '3a8c765f3e34ee10383f5a2fc9ce3860bba4b59ae631aa43797ecdf184849869'
RETAIL_OBJECT = 'c-qZYO>7%Q6n^`YcpDb#6ay8q$i}iz1gT{wOEM`v*oo~@lsc6gK@Uao#@^Hxwl`XDQIM==F+NlrkR>=EfkZAu>AeSzs23!J5UP6Uu?U2EK&ae$GjArd_Ihi?&xw&|=e_TJ^Y+a*v%B8Ut>*<%fI$-=!mfj++;i!mGiMH_AOybl>1_W|TM-Y>l>i75dpMr}$fOL=J|P{t62Lt2G9CB=ZIyIEz?jOhn`1C%3|1P0t&hRT7%V;p3sak7tI#ja%b=w@aGI?F>wW{*PfBczM!TRg9N2tlmt&D0uF1u9wiW4+%tE-}f`&Rg@N_^8;-CBk(bs=Q-abkv_4~aUfOJRDnKoadMhBR)#5IzcMgrClo|9R9O0NRYm07+2dmMFC$yX3UEeYAjwc$A+2ZBp=bZ0=G1G;t~!~lh1I3ljLB}mh~7||WMsFi|U#U4hT;~%1yTx*SM{m7?v1hrO~)-&{gGM$O<z8dPRokQJw`=H<)ndYYVLO(pFUS(wlB5ogJ?s2}hB<+!dFr+_#2b=J)PxlP#zTN&d79m{?Hotj%qo;sOeQHyzcLa(T$5@!+1OEsjh(!aKhS*#Hn@3C!U<9#r0Lvn_&gwXVOK4xg@#=~KCESy%yJZN`=b&Aa4udt*I+3R$?;$;_L_%FqN7P&mo^cq{a;fBUaxt}dwqQA$*|e@-t7^qUrkJ~|RgGq)ZYHKEXC=9mOr6c!rl}dWX=s*HHEqp7ik8V<(YCMe?3gxEX~U~J$<x1xw#@Ax@LlBLchUCndjL;Qar;-_+~0?Dg;M}eaa?!_ZH|jkfM@tzF$r+ev-1EaIA44dZI8b`yq9=mm{a`7m-B0Yu*dm+nE#3Pf@jFk|HB`UM&7^77Xv>2pu^XroI2(&QyY7o`|sd12hBb1U*gl_)5rPNsEz$q?$iC<pb4i%=6}rjk?G_6)u@f(F8AN_>Ir*aj!|C;_$NpFhS_MD4rGe-P~ecM*R3+xO*|g0L>aCbyIaYnEs|W&lS}&YmTgrG$AFzCg%<Q&Y7Oe!bsqOSujR>rl_!J;^o7hyPWJ+f`oh50vnkz2%Hk<V*k;{GIOd)MiL%vbm`yaAmSZMbyY(8{+pQKPTGf_gJH|Fz-uQlljl5RY)~t&8wqe^f%bpTtQ4mCUejfg|34^0Cs--f(m47q}e}Vs-M$h=^^SMItGFv@B#Y9zh&p4J<f4AmnsRT(Zo@rH6oGV}4$QC?q!>BcV_yrI5<<7o!p|}~q!Hr#vxbca{?&_@{nH?)c-Pp!WhQ%kN*w3@r>aAbkzqd)QwfD|Q<I(=j7ng@P<MHQEPWzrG|Gvy}Tk>t?XJdE*&z<J^dU&~yeZm)0f&K09Kl>9^42OBW6P!o=<mf#o_we%hnDg}VC@=IZu+Q!jJazOxU<kjoa67=G{kiX6>D=)xPYdvvet!Z|M1vj'

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path)
    parser.add_argument('stamp', type=Path)
    args = parser.parse_args()
    compiled = args.object.read_bytes()
    actual = hashlib.sha256(compiled).hexdigest()
    if actual != INPUT_OBJECT_SHA256:
        raise SystemExit('unexpected RNARES compiler object: ' + actual)
    retail = zlib.decompress(base64.b85decode(RETAIL_OBJECT))
    if hashlib.sha256(retail).hexdigest() != OUTPUT_OBJECT_SHA256:
        raise SystemExit('corrupt embedded RNARES layout')
    args.object.write_bytes(retail)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()

if __name__ == '__main__':
    main()
