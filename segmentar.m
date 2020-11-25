clear variables;

imds = imageDatastore("/home/lassa97/Desktop/Master/PSM/scanego/imgs");

segmentador = segmentador();

num_images = size(imds.Files);

display = figure('NumberTitle', 'off', 'Name', sprintf('Image: %s.png', 0));

for num=1:num_images
    image = readimage(imds, num);
    
    filtered_image = filtrar(segmentador, image);
    
    binary_image = binarizar(segmentador, filtered_image);
    
    [labeled_image, color_labeled_image] = etiquetar(segmentador, binary_image);
    %imfill(binary_image, 'holes');
    
    centroides = extraer_centroides(segmentador, labeled_image);
    
    areas = extraer_areas(segmentador, labeled_image);
    
    bordes = extraer_bordes(segmentador, binary_image);
    
    set(display, 'NumberTitle', 'off', 'Name', sprintf('Image: %i.png', num));
    
    subplot(121);
    imshow(image);
    
    subplot(122);
    plot(segmentador, color_labeled_image, centroides, areas, bordes);
    
    pause;
end

close(display);