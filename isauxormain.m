function y=isauxormain(stroke1,stroke2)
yrange=[(min(stroke2.points(:,2)))-(0.4*(range(stroke2.points(:,2)))),(min(stroke2.points(:,2)))+(0.4*(range(stroke2.points(:,2))))];
if (min(stroke1.points(:,2))>yrange(1))&&(min(stroke1.points(:,2))<yrange(2))
    y=1;
else y=0;
end 
end 