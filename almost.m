
load('complete_wrong_data_730')
 m=1;
   % y=[];
    nstrokearray=[];

for j=1:X(7).nchars
for k=1:X(7).chararr(j).nsgs%Loop over each sgarray in the character
         for l=1:X(7).chararr(j).sgarray(k).nstrokes%loop over each stroke
             nstrokearray(m).points=X(7).chararr(j).sgarray(k).strokearray(l).points;
             m=m+1;
            
         end
          end
 end
 for p=1:length(nstrokearray)
  plot(nstrokearray(p).points(:,1),nstrokearray(p).points(:,2));hold on;
 end
 
 csg.stroke(1).points=nstrokearray(1).points;
 
 nstrokearray(1)=[];
 
 minx=[];
for i=1:length(nstrokearray)
    minx=[minx min(nstrokearray(i).points(:,1))];
end
[~,ind]=sort(minx);
test=nstrokearray;
nstrokearray=nstrokearray(ind);

for i=1:size(nstrokearray)
    
    val1=isabove(nstrokearray(i),csg.stroke(1))%Checking if the stroke is a top stroke
         if val1==1
        csg.stroke=[csg.stroke nstrokearray(i)];
    nstrokearray(i)=[];
         end
         
         val2=isbelow(nstrokearray(1),csg.stroke(1))%Checking if the stroke is a bottom stroke
        if val2==1
        csg.stroke=[csg.stroke nstrokearray(i)];
        nstrokearray(i)=[];
        end
        
        
end
   
yrange=[(min(csg.stroke(1).points(:,2)))-(0.2*(range(csg.stroke(1).points(:,2)))),(min(csg.stroke(1).points(:,2)))+(0.2*(range(csg.stroke(1).points(:,2))))];
if (min(stroke1.points(:,2))>yrange(1))&&(min(stroke1.points(:,2))<yrange(2))
    y=1;
else y=0;
end 


    val3=isauxormain(nstrokearray(i),csg.stroke(1))
      if val3==1
           Baux=isBaux(nstrokearray(i))    %Checking if the stroke is a baseline auxiliary stroke
        if Baux==1
            csg.stroke=[csg.stroke nstrokearray(i)];
        nstrokearray(i)=[];
       
        else
            val4=1
             nsg=nstrokearray(i);
             newXstrokearray=cat(1,newXstrokearray,csg.stroke);      
        csg.stroke(1)=nsg;
        end
        
        
      end
      

