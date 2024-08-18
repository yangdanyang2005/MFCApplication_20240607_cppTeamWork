% 禁用所有警告
warning('off', 'all');

% 禁用命令窗口输出
diary('NUL');  % 对于 Windows

% 读取 CSV 文件中的数据 ——
% 获取当前脚本所在的文件夹路径
scriptFolder = fileparts(mfilename("fullpath"));

% 构建 gcp.csv 文件的相对路径
dataFile = fullfile(scriptFolder, '..', 'gcp_data', 'gcp.csv');

% 读取文件
data = readmatrix(dataFile, 'NumHeaderLines', 1);%使用 readmatrix 函数并通过 NumHeaderLines 参数跳过文件的第一行。该参数指定要跳过的行数。

% 提取 x, y, z 列以及点名列
x = data(:, 3);
y = data(:, 4);
z = data(:, 5);
names = data(:, 2);

% 假设数据需要转换为网格形式才能绘制表面图
% 创建 X 和 Y 的网格
% 假设 x 和 y 的数据是按网格顺序排列的
x_unique = unique(x);
y_unique = unique(y);

[X, Y] = meshgrid(x_unique, y_unique);

% 根据 x 和 y 网格，插值得到 z 值
Z = griddata(x, y, z, X, Y, 'cubic');

% 绘制三维表面图
figure;
h1 = surf(X, Y, Z);%可以在图形对象前面添加句柄，以便在后续操作中使用。
% 例如写h1 = surf(X, Y, Z);等等，在后面添加图例的时候就可以写legend([h1, h2, h3], {'表面图', '等高线', '数据点'});使用句柄添加图例
% 但是在这里会报错：错误使用 matlab.graphics.chart.primitive.Surface/horzcat无法将双精度值 x.xxxxx 转换为句柄

% 设置坐标轴标签
xlabel('北坐标X');
ylabel('东坐标Y');
zlabel('高程Z');


hold on;  % 保持当前图形
h2 = contour3(X, Y, Z, 20, 'LineColor', 'black', 'LineWidth', 1);% 添加等高线到表面图，显示地形的轮廓
h3 = plot3(x, y, z, 'ro', 'MarkerSize', 2, 'MarkerFaceColor', 'r');% 在三维表面图上添加数据点
% 解释代码：
% plot3 是 MATLAB 中用于绘制三维散点图的函数。
% x, y, z 分别是数据点的 X、Y、Z 坐标的向量。
% 这个函数会在三维图中根据这些坐标绘制点。
% 'ro':
% 'r' 表示点的颜色为红色（red）。
% 'o' 表示点的标记符号为圆形（circle）。
% 所以 'ro' 代表绘制红色圆形标记的点。
% 'MarkerSize', 2:
% 'MarkerSize' 是一个属性，用于指定标记的大小。
% 2 表示标记的大小为 2（单位是 MATLAB 中的默认单位）。
% 'MarkerFaceColor', 'r':
% 'MarkerFaceColor' 是一个属性，用于指定标记内部的填充颜色。
% 'r' 表示填充颜色为红色。

% 添加每个点的名称
% for i = 1:length(x)
%     text(x(i), y(i), z(i), names(i), 'VerticalAlignment', 'bottom', 'HorizontalAlignment', 'right');
% end

% 打印句柄以检查是否正确
disp('句柄 h1:');
disp(h1);
disp('句柄 h2:');
disp(h2);
disp('句柄 h3:');
disp(h3);


hold off;  % 释放图形保持

% 设置图形的视角，使地形图更加立体
view(45, 30);

% 显示网格
grid on;

% 设置标题
title('由数据文件生成的三维表面图');

% 设置渐变色地形图的颜色映射
colormap(parula);  % 使用 parula 渐变色调
% 你也可以尝试其他颜色映射，比如 colormap(jet), colormap(hot) 等

% 添加颜色条
colorbar;

% 设置着色效果为插值着色，使表面平滑
shading interp;

% 添加图例
% 确保传递的是图形对象句柄
try
    legend('表面图', '等高线', '数据点', 'Location', 'best');%不使用句柄添加图例
catch ME
    disp('错误发生在 legend 函数调用中：');
    disp(ME.message);
end

% 设置图形窗口的标题
set(gcf, 'Name', '由数据文件生成的三维表面图', 'NumberTitle', 'off');
% 代码解释：
% gcf：这是一个 MATLAB 函数，表示“获取当前图形”（Get Current Figure）。它返回当前活动图形窗口的句柄。
% set：这是一个 MATLAB 函数，用于修改图形对象的属性。
% 'Name', '由数据文件生成的三维表面图'：这是 set 函数的一个参数，表示要设置图形窗口的标题。'三维表面图' 是你为图形窗口指定的标题文本。
% 'NumberTitle', 'off'：这是 set 函数的另一个参数，'NumberTitle' 属性用于控制图形窗口标题中是否显示窗口的编号。如果设置为 'off'，则图形窗口的标题只显示你指定的标题文本，不包括窗口的编号。如果设置为 'on'，标题将包含窗口编号（例如，“Figure 1”）。

% 保持图形窗口
waitfor(gcf); % 等待用户关闭图形窗口