%num = 1;

for num=1:29
    img = im2double(imread("imgs/7-" + num + ".png"));    
    subplot(221);
    imshow(img, []);

    gray = rgb2gray(img);
    pixelCount = imhist(gray);
    %T = otsuthresh(pixelCount);
    subplot(222);
    bar(pixelCount);
    threshold = 125/255;
    BW = imbinarize(gray, threshold);
    label = bwlabel(BW, 8);
    color = label2rgb(label);
    subplot(223);
    imshow(color, []);

    BW = imfill(BW, "holes");
    label = bwlabel(BW, 8);
    color = label2rgb(label);

    subplot(224);
    imshow(color, []);

    s = regionprops(BW);

    elements = size(s);

    for i=elements(1):-1:1
        if s(i).Area < 1000
            s(i) = [];
        end
    end

    elements = size(s);

    centroids = cat(1, s.Centroid);
    areas = cat(1, s.BoundingBox);
    hold on
    plot(centroids(:,1), centroids(:,2), 'k*');
    dim = zeros(1, 4);
    for i=1:elements(1)
        dim = areas(i,:);
        rectangle('Position', dim);
    end
    hold off
    
    pause;
end