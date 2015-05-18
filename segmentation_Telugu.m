%Segmentation for Telugu Characters
clear all
clc
load('complete_wrong_data_730')
newX=X;
 
for i=7:length(X)%loop over each word
   m=1;
    y=[];
    nstrokearray=[];
 for j=1:X(i).nchars%loop over each character in the word
     for k=1:X(i).chararr(j).nsgs%Loop over each sgarray in the character
         for l=1:X(i).chararr(j).sgarray(k).nstrokes%loop over each stroke
             nstrokearray(m).points=X(i).chararr(j).sgarray(k).strokearray(l).points;
             m=m+1;
         end
         
     end
 end
 m=m-1
 segm(nstrokearray)
 word(i).label=X(i).label;
 %newX(i)=constructstruct(newXstrkgrp);
end