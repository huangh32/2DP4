clc
clear all
s=serial('COM48','BaudRate',9600,'Terminator','CR');
fopen(s);
t=100;



while 1
for n=1:t
val(n)=str2double(fgetl(s))*5/(2^8-1); %fgetl(s) returns a value in type 'str' as t increase by 1
plot(val);
title('Serial Data');%title
xlabel('Sample number'); % x-axis label
ylabel('Voltage value'); % y-axis label
axis([0, t, 1.5, 5]); % Set the limits for the x-axis which is x to x+50 and set the minimum y-axis limit which is 0 to 200.

grid
drawnow;%function
end

end

fclose(s);

delete(s);

clear s;


  
 
