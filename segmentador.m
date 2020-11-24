classdef segmentador
    %UNTITLED2 Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        filtro = fspecial('disk', 3);
        threshold = 125/255;
    end
    
    methods
        function filtered_image = filtrar(segmentador, image)
            %filtrar: Devuelve la imagen filtrada mediante el filtro 
            %        definido para el segmentador
            image = im2double(image);
            filtered_image = imfilter(image, segmentador.filtro);
        end
        
        function binary_image = binarizar(segmentador, filtered_image)
            %binarizar: Devuelve la imagen binaria correspondiente
            %           a la imagen filtrada
            gray_image = rgb2gray(filtered_image);
            
            binary_image = imbinarize(gray_image, segmentador.threshold);
        end
        
        function [labeled_image, color_labeled_image] = etiquetar(~, binary_image)
            %etiquetar: Devuelve las regiones etiquetadas y coloreadas
            labeled_image = bwlabel(binary_image, 8);
            color_labeled_image = label2rgb(labeled_image);
        end
        
        function centroides = extraer_centroides(~, labeled_image)
            %extraer_centroides: Extrae los centroides de cada una de
            %                    las regiones detectadas
            regions = regionprops(logical(labeled_image));
            num_regions = size(regions);
            for i=num_regions(1):-1:1
                if regions(i).Area < 1000
                    regions(i) = [];
                end
            end
            
            centroides = cat(1, regions.Centroid);
        end
        
        function areas = extraer_areas(~, labeled_image)
            %extraer_areas: Extrae las areas de cada una de las 
            %               regiones detectadas
            regions = regionprops(logical(labeled_image));
            zonas = cat(1, regions.BoundingBox);
            num_regions = size(regions);
            areas = NaN(num_regions(1), 4);
            for i=1:num_regions(1)
                areas(i,1:4) = zonas(i,:);
            end
        end
        
        function bordes = extraer_bordes(~, binary_image)
            %extaer_bordes: Extrae los bordes de cada una de las
            %               regiones detectadas
            bounds = bwboundaries(binary_image, 8);
            num_bounds = size(bounds);
            for i=num_bounds(1):-1:1
                length = size(bounds{i});
                if length(1) < 100
                    bounds(i,:) = [];
                end
            end
            bordes = bounds;
            
        end
        
        function plot(~, color_labeled_image, centroides, areas, bordes)
            %plot:  Dibuja las regiones coloreadas y sus respectivos 
            %       centroides, areas y bordes
            imshow(color_labeled_image, []);
            hold on;
            num_areas = size(areas);
            for i=1:num_areas(1)
                rectangle('Position', areas(i,:));
            end
            
            num_bounds = size(bordes);
            for i=1:num_bounds(1)
                bound = bordes{i};
                plot(bound(:,2), bound(:,1), 'g', 'LineWidth', 2);
            end
            plot(centroides(:,1), centroides(:,2), 'k*');
            hold off;
        end
    end
end

