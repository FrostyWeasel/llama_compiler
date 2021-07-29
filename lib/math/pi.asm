; double pi ();
; -------------
; This function returns the real number pi (3.1415926535...).


             section .text
             global _pi

_pi          push      rbp
             mov       rbp, rsp
             fldpi
             pop       rbp
             ret
