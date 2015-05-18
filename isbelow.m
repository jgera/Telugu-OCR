function y=isbelow(stroke1,stroke2)

if isoverlapping(stroke1,stroke2)
    %[x1,y1]=intersections(stroke1.points(:,1),stroke2.points(:,2),stroke2.points(:,1),stroke2.points(:,2),0);
   % if (~isempty(x1))
     %   if y1<(mean(stroke2.points(:,2)))
      %      y=1;
       % else
        %    y=0;
       % end
  %  else
        if max(stroke1.points(:,2))<(0.3*range(stroke2.points(:,2))+min(stroke2.points(:,2)))
            y=1;
        else
            y=0;
        end
    
else
    y=0;
end

            
            
        



