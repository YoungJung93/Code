% circle([50,50],50,5,'b');
x=[0 0 7 7 0]; 
y=[0 7 7 0 0];
plot(x,y,'k') % 밖 테두리
hold on
% x=[0 0 90 90 0]; 
% y=[0 60 60 0 0];
% plot(x,y,'k') % 안 테두리
% hold on
% x=[0 0 10 10 0];
% y=[0 15 15 0 0];
% plot(x,y,'k') % 1번
% hold on
% x=[20 20 40 40 20];
% y=[0 15 15 0 0];
% plot(x,y,'k') % 2번
% hold on
% x=[50 50 70 70 50];
% y=[0 15 15 0 0];
% plot(x,y,'k') % 3번
% hold on
% x=[80 80 90 90 80];
% y=[0 15 15 0 0];
% plot(x,y,'k') % 4번
% hold on
% x=[0 0 10 10 0];
% y=[25 40 40 25 25];
% plot(x,y,'k') % 5번
% hold on
% x=[20 20 40 40 20];
% y=[25 40 40 25 25];
% plot(x,y,'k') % 6번
% hold on
% x=[50 50 70 70 50];
% y=[25 40 40 25 25];
% plot(x,y,'k') % 7번
% hold on
% x=[80 80 90 90 80];
% y=[25 40 40 25 25];
% plot(x,y,'k') % 8번
% hold on
% x=[0 0 10 10 0];
% y=[50 60 60 50 50];
% plot(x,y,'k') % 9번
% hold on
% x=[20 20 40 40 20];
% y=[50 60 60 50 50];
% plot(x,y,'k') % 10번
% hold on
% x=[50 50 70 70 50];
% y=[50 60 60 50 50];
% plot(x,y,'k') % 11번
% hold on
% x=[80 80 90 90 80];
% y=[50 60 60 50 50];
% plot(x,y,'k') % 12번
% hold on
% x=[0 0 20 20 0]; 
% y=[0 45 45 0 0];
% plot(x,y,'k') % 1번
% hold on
% x=[35 35 55 55 35]; 
% y=[35 60 60 35 35];
% plot(x,y,'k') % 2번
% hold on
% x=[35 35 55 55 35]; 
% y=[0 20 20 0 0];
% plot(x,y,'k') % 3번
% hold on
% x=[70 70 90 90 70]; 
% y=[40 60 60 40 40];
% plot(x,y,'k') % 4번
% hold on
% x=[70 70 90 90 70]; 
% y=[0 25 25 0 0];
% plot(x,y,'k') % 5번
% hold on
% text(92,33,'exit');


clear all;clc;
delete(instrfindall)
s1=serial('COM17','BaudRate',115200);
fopen(s1);
pause(.010);
while (1)
    x=str2double(fscanf(s1));
    y=str2double(fscanf(s1));
    plot(x,y,'k*:');
    %scatter(x,y,'k','filled');
    drawnow;
    plot(x,y,'w*:');
end
fclose(s1);
delete(instrfindall);