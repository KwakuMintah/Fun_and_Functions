clear all;
load("Chladni.m");

chladniOne = Chladni(:,1);
chladniTwo = Chladni(:,2);
chladniThree = Chladni(:,3);
chladniFour = Chladni(:,4);
chladniFive = Chladni(:,5);
chladniSix = Chladni(:,6);

sizeMat = size(Chladni);
side = sqrt(sizeMat(1));

EOne = reshape(chladniOne,side,side);
ETwo = reshape(chladniTwo,side,side);
EThree = reshape(chladniThree,side,side);
EFour = reshape(chladniFour,side,side);
EFive = reshape(chladniFive,side,side);
ESix = reshape(chladniSix,side,side);

figOne = imagesc(ESix);