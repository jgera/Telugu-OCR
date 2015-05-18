%Function for segmenting telugu characters
%ret below is taken temporarly and we need to segregate different stroke
%group according to segmented characters and thus forming the final X
%struct cell
function segm(nstrokearray)
csg.stroke(1).points=nstrokearray(1).points; % 1st main stroke
nstrokearray(1)=[];
%newXstrokearray=struct([]);
%sorting the strokearray wrt to minimum x
minx=[];
for i=1:length(nstrokearray)
    minx=[minx min(nstrokearray(i).points(:,1))];
end
[~,ind]=sort(minx);

nstrokearray=nstrokearray(ind);

for i=1:size(nstrokearray)
    
    if isabove(nstrokearray(i),csg.stroke(1))%Checking if the stroke is a top stroke
         if y==1
        csg.stroke=[csg.stroke nstrokearray(i)];
    nstrokearray(i)=[];
         end
    elseif isbelow(nstrokearray(1),csg.stroke(1))%Checking if the stroke is a bottom stroke
        if y==1
        csg.stroke=[csg.stroke nstrokearray(i)];
        nstrokearray(i)=[];
        end
    elseif isauxormain(nstrokearray(i),csg.stroke(1))%Checking if the stroke is an auxiliary stroke or main stroke by checking the starting point whether it 
           %lies in the range  +-20% of the hieght of the main stroke from
           %the base line.
                                                    
                                                 
        Baux=isBaux(nstrokearray(i));     %Checking if the stroke is a baseline auxiliary stroke
        if Baux==1
            csg.stroke=[csg.stroke nstrokearray(i)];
        nstrokearray(i)=[];
               % if i<size(nstrokearray)
              %       nsg.stroke(1)=nstrokearray(i+1);
              %  end
        else
            nsg=nstrokearray(i);
             %newXstrokearray=cat(1,newXstrokearray,csg.stroke);      
        csg.stroke(1)=nsg;
        end
            
      
           
            nstrokearray(i)=[];
    
    end       
     end



   
        