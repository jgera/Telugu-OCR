function y=isabove(stroke1,stroke2)

if isoverlapping(stroke1,stroke2)
    %[x1,y1]=intersections(stroke1.points(:,1),stroke1.points(:,2),stroke2.points(:,1),stroke2.points(:,2),0);
   % if (~isempty(x1))
    %    if y1>(mean(stroke2.points(:,2)))
     %       y=1;
      %  else
       %     y=0;
       % end
   % else
        if min(stroke1.points(:,2))>(max(stroke2.points(:,2))-0.2*(range(stroke2.points(:,2))))
            y=1;
        else
            y=0;
        end
    
else
    y=0;
end
        
            
        



