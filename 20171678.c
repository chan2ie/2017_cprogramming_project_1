#include <stdio.h>
#include <stdlib.h>

struct coordinate {
    int x;
    int y;
};

int run_function ();
int read_image (int *height, int *width, char*** image);
int check_size (int height, int width);
char** make_board (char** image, int height, int width);
int get_character (char*** image, int height, int width);
int run_query (int *height, int *width, char*** image);
int run_query_1 (int *height, int* width, char*** image);
int run_query_2 (int *height, int* width, char*** image);
int run_query_3 (int *height, int* width, char*** image);
int run_query_4 (int *height, int* width, char*** image);
int run_query_5 (int *height, int* width, char*** image);
void print_image (int height, int width, char** image);
void swap (char* ch1, char* ch2);
void free_canvas (int height, char** image);
char** realloc_canvas (int height, int width, char** image);
char** resize (int arg1, int* height, int* width, char** image);
char** rotate (int* height, int* width, int angle, char** image);
char** fill (int x, int y, char color, int height, int width, char** image);
void flip (int height, int width, int flag, char*** image);
char* copy (int x1, int y1, int c_h, int c_w, int height, int width, char** image);
void paste (int x2, int y2, int height, int width, char** image, char* temp);
struct coordinate* expand_queue (int *size, struct coordinate *queue);

int main(){
	int testcase;
    int i;
	printf("Input testcase : ");
	scanf("%d", &testcase);

	for(i = 0; i < testcase; i++){
		run_function();
	}

	return 0;
}

int run_function(){
	char** image;
    int height, width;
	int testcase_query;
    int i;

	if (read_image(&height, &width, &image) == 1){
		return 1;
	}
   
    printf("Input number of query : ");
	scanf("%d", &testcase_query);

	for(i = 0; i < testcase_query; i++){
		run_query(&height, &width, &image);
	}	

    free_canvas(height, image);

    return 0;
}

int read_image(int *height, int *width, char*** image_address){
    char** image;
    int error_type;

	printf("Input height, width : ");
	scanf("%d%d", height, width);
		
	if(check_size(*height, *width) == 1){
		printf("!ERROR! : Your canvas cannot be bigger than 4096 * 4096.\n");
		return 1;
	}

	image = make_board(image, *height, *width);

	printf("Input the image :\n");
    error_type = get_character(&image, *height, *width);
	if(error_type == 1){
		printf("!ERROR! : Your image is bigger than your canvas.\n");
		return 1;
	}
    if(error_type == 2){
        printf("!ERROR! : Your image is smaller than your canvas.\n");
        return 1;
    }

    *image_address = image;
	return 0;
}

int check_size(int height, int width){

	if(height > 4096 || width > 4096){
		return 1;
	}
	return 0;
}

char** make_board(char** image, int height, int width){
    int i;

	image = (char**)malloc(height*sizeof(char*));

	for(i = 0; i < height; i++){
		image[i] = (char*)malloc(width*sizeof(char));
	}

	return image;
}

int get_character(char*** image, int height, int width){
	char temp;
    char **temp_image = *image;
	int i, j;
    getchar();

	for(i = 0; i < height; i++){
		for(j = 0; j < width + 3; j++){
			scanf("%c", &temp);
			if(j == width && temp == '\n'){
				break;
			}
			if(j == width && temp != '\n'){
				return 1;
			}
            if(j != width && temp == '\n'){
                return 2;
            }

			temp_image[i][j] = temp;
		}
	}

	return 0;
}

int run_query (int *height, int *width, char*** image){
	int which_query;

	printf("Input query : ");
	scanf("%d", &which_query);
	
	switch(which_query){
		case 1 : 
			run_query_1(height, width, image);
			break;
		case 2 :
			run_query_2(height, width, image);
			break;
		case 3 :
            run_query_3(height, width, image);
			break;
		case 4 :
            run_query_4(height, width, image);
			break;
		case 5 : 
            run_query_5(height, width, image);
			break;

		default :
			printf("!ERROR! : That is not a valid choice.\n");
	}

	return 0;
}

int run_query_1(int *height, int *width, char*** image){
    int option, temp;
    
    printf("\nResize\n");
    printf("Input 0 or 1 : ");
    scanf("%d", &option);
    
    if(option != 0 && option != 1){
        printf("!ERROR! : That is not a valid choice.\n");
        print_image(*height, *width,  *image);
        return 1;
    }

    temp = *height;

    *image = resize(option, height, width, *image);

    if(temp == *height){
        print_image(*height, *width,  *image);
        return 1;
    }

    printf("Result_resize height : %d, width : %d\n",*height, *width);
    print_image(*height, *width,  *image);

    return 0;
}

int run_query_2(int *height, int *width, char*** image){
    int option;

    printf("\nRotate\n");
    printf("Input 0 or 1 or 2 : ");
    scanf("%d", &option);
    
    if(option != 0 && option != 1 && option != 2){
        printf("!ERROR! : That is not a valid choice.\n");
        print_image(*height, *width,  *image);
        return 1;
    }

    *image = rotate(height, width, option, *image);

    printf("Result_rotate height : %d, width : %d\n",*height, *width);
    print_image(*height, *width,  *image);

    return 0;
}

int run_query_3(int *height, int *width, char*** image){
    int option;

    printf("\nFlip\n");
    printf("Input 0 or 1 : ");
    scanf("%d", &option);
    
    if(option != 0 && option != 1){
        printf("!ERROR! : That is not a valid choice.\n");
        print_image(*height, *width,  *image);
        return 1;
    }

    flip(*height, *width, option, image);
    
    print_image(*height, *width,  *image);

    return 0;
}

int run_query_4(int *height, int *width, char*** image){
    int x1, y1, c_h, c_w, x2, y2;
    char* temp;

    printf("\nCopy and Paste\n");
    printf("x1, y1, c_h, c_w, x2, y2 : ");
    scanf("%d%d%d%d%d%d",&x1, &y1, &c_h, &c_w, &x2, &y2);
    
    if(x1 < 0 || y1 < 0 || x1 >= *width || y1 >= *height){
        printf("!ERROR! : Your coordinate is depart from your image.\n");
        print_image(*height, *width, *image);
        return 1;
    }

    if(c_h < 1 || c_w < 1){
        printf("!ERROR! : Your copy area is too small.\n");
        print_image(*height, *width, *image);
        return 1;
    }

    if(c_h > 4096 || c_w > 4096){
        printf("!ERROR! : Your copy area is too small.\n");
        print_image(*height, *width, *image);
        return 1;
    }

    temp = copy(x1, y1, c_h, c_w, *height, *width, *image);
    paste(x2, y2, *height, *width, *image, temp);

    print_image(*height, *width,  *image);
    
    return 0;
}

int run_query_5(int *height, int *width, char*** image){
    int y, x;
    char color;

    printf("\nFill\n");
    printf("Input y, x, color : ");
    scanf("%d%d %c",&x,&y,&color);

    if(y < 0 || x < 0 || x >= *height || y >= *width){
        printf("!ERROR! : That is not a valid coordinate.\n");
        print_image(*height, *width, *image);
        return 1;
    }
    if((*image)[x][y] == color){
        printf("!ERROR! : That is not a valid color.\n");
        print_image(*height, *width, *image);
        return 1;
    }

    *image = fill(x, y, color, *height, *width, *image);

    print_image(*height, *width, *image);

    return 0;
}

char** resize(int arg1, int* height, int* width, char** image){
	char** result_image;
    int i, j;

    if(arg1 == 0){
        if(check_size(*height * 2, *width * 2) == 1){
            printf("!ERROR! : Your image is too big to expand.\n");
        }
        result_image = make_board(result_image, *height * 2, *width * 2);

        for(i = 0; i < *height; i++){
            for(j = 0; j < *width; j++){
                result_image[2 * i][2 * j] = (image)[i][j];
                result_image[2 * i + 1][2 * j] = (image)[i][j];
                result_image[2 * i][2 * j + 1] = (image)[i][j];
                result_image[2 * i + 1][2 * j + 1] = (image)[i][j];
            }
        }
        
        free_canvas(*height, image);
        *height = *height * 2;
        *width = *width * 2;
        

        return result_image;
    }
    if(arg1 == 1){
        if(*height == 1 || *width == 1){
            printf("!ERROR! : Your image is too small to down-size.\n");
        }
        result_image = make_board(result_image, *height / 2, *width / 2);

        for(i = 0; i < *height / 2; i++){
            for(j = 0; j < *width / 2; j++){
                result_image[i][j] = (image[2 * i][2 * j]
                                    + image[2 * i + 1][2 * j]
                                    + image[2 * i][2 * j + 1]
                                    + image[2 * i + 1][2 * j + 1]) / 4;
            }
        }
        
        free_canvas(*height, image);
        *height = *height / 2;
        *width = *width / 2;
    
        return result_image;
    }
}

char** rotate(int *height, int *width, int angle, char** image){
    char** result_image;
    int temp, count, i , j;
    result_image = make_board(result_image, *height, *width);

    for(count = 0; count <= angle; count++){
        result_image = realloc_canvas(*width, *height, result_image);

		for(i = 0; i < *height; i++){
			for(j = 0; j < *width; j++){
				result_image[j][*height - 1 - i] = image[i][j];
			}
		}

		free_canvas(*height, image);
		
		temp = *height;
		*height = *width;
		*width = temp;
		
		image = result_image;

        if (count != angle) {
            result_image = make_board(result_image, *height, *width);
        }
	}

	return image;
}

void flip(int height, int width, int flag, char*** image){
    int i, j;
    
    if(flag == 0){
        for(i = 0; i < height/2; i++){
            for(j = 0; j < width; j++){
                swap(&(*image)[i][j], &(*image)[height - i -1 ][j]);
            }
        }
    }
    if(flag == 1){
        for(j = 0; j < width/2; j++){
            for(i = 0; i < height; i++){
                swap(&(*image)[i][j], &(*image)[i][width - j - 1]);
            }
        }
    }
}

char* copy(int x1, int y1, int c_h, int c_w, int height, int width, char** image){
    int x_end, y_end, count = 2;
    char* temp;
    int i, j;

    if(x1 + c_w > width){
        x_end = width - 1;
    }
    else{
        x_end = x1 + c_w - 1;
    }

    if(y1 + c_h > height){
        y_end = height - 1;
    }
    else{
        y_end = y1 + c_h - 1;
    }
    
    temp = malloc(((x_end + 1)*(y_end + 1) + 2) * sizeof(char));
    
    temp[0] = y_end - y1 + 1;
    temp[1] = x_end - x1 + 1;

    for(i = y1; i <= y_end; i++){
        for(j = x1; j <= x_end; j++){
            temp[count] = image[i][j];
            count++;
        }
    }
    return temp;
}

void paste(int x2, int y2, int height, int width, char** image, char* temp){
    int i = y2, j = x2, count = 2, linenum = 1;

    while(1){
        if(i >= height){
            break;
        }
        while(1){
            if(count == 2 + (temp[1]*linenum)){
                linenum++;
                j = x2;
                break;
            }
            if(j >= width){
                 count = 2 + (temp[1])*linenum;
                 j = x2;
                 linenum++;
                break;
            }
            image[i][j] = temp[count];
            j++;
            count++;
        }
        i++;
    }

    free(temp);
}

char** fill(int x, int y, char color, int height, int width, char** image){
    int size = 1, count = 0;
    char check;

    struct coordinate *queue = malloc(size * sizeof(struct coordinate));

    check = image[x][y];

    queue[count].x = x;
    queue[count].y = y;

    while(1){
        if(queue[count].x > 0){
            if(image[queue[count].x - 1][queue[count].y] == check){
                queue = expand_queue(&size, queue);
                queue[size - 1].x = queue[count].x - 1;
                queue[size - 1].y = queue[count].y;
            }
        }
        if(queue[count].y > 0){
            if(image[queue[count].x][queue[count].y - 1] == check){
                queue = expand_queue(&size, queue);
                queue[size - 1].x = queue[count].x;
                queue[size - 1].y = queue[count].y - 1;
            }
        }
        if(queue[count].x < height - 1){
            if(image[queue[count].x + 1][queue[count].y] == check){
                queue = expand_queue(&size, queue);
                queue[size - 1].x = queue[count].x + 1;
                queue[size - 1].y = queue[count].y;
            }
        }
        if(queue[count].y < width - 1){
            if(image[queue[count].x][queue[count].y + 1] == check){
                queue = expand_queue(&size, queue);
                queue[size - 1].x = queue[count].x;
                queue[size - 1].y = queue[count].y + 1;
            }
        }
        image[queue[count].x][queue[count].y] = color;
        
        count++;

        if(size <= count){
            break;
        }
    }
    printf("Number of colored pixels = %d\n",size);
    
    free(queue);

    return image;
}

void swap(char* ch1, char* ch2){
    char temp;

    temp = *ch1;
    *ch1 = *ch2;
    *ch2 = temp;
}

void free_canvas(int height, char** image){
    int i;

    for(i = 0; i < height; i++){
        free(image[i]);
    }
    free(image);
}

char** realloc_canvas(int height, int width, char** image){
    int prev_height = width;
    int prev_width = height;
    int i;

    int min_height = prev_height < height ? prev_height : height;
    for (i = height; i < prev_height; ++i)
        free(image[i]);

    image = realloc(image, height * sizeof(char*));
    for (i = 0; i < min_height; i ++) {
		image[i] = realloc(image[i], width*sizeof(char));
    }
    for (i = min_height; i < height; i ++) {
        image[i] = malloc(width * sizeof(char));
    }

    return image;
}

void print_image(int height, int width, char** image){
	int i, j;
    
    printf("Result Image\n\n");

	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){
			printf("%c",image[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

struct coordinate* expand_queue(int *size, struct coordinate *queue){
    *size += 1;
    queue = realloc(queue, *size * sizeof(struct coordinate));

    return queue;
}
