% open file
f = fopen('debug013.dat');

% make array and plot
y = fread(f, Inf, 'int16');
plot(y);