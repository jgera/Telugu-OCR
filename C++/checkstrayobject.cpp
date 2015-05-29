function y=checkstrayobject(stroke1,stroke2)

d1=isabove(stroke1,stroke2);
d2=isbelow(stroke1,stroke2);

if d1+d2>=1
    y=1;
else
    y=0;
end
