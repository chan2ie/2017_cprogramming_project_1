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
    //get testcase and run run_function testcase times
	int testcase;
    int i;
	printf("Input testcase : ");
	if(scanf("%d", &testcase) != 1){
        printf("!ERROR! : That is not a valid choice\n");
        return 0;
    }
    //if testcase is not a number, throw error

	for(i = 0; i < testcase; i++){
		run_function();
	}

	return 0;
}

int run_function(){
    //read image with read_image and get number of testcase
    //then, run query testcase times and free image
	char** image;
    int height, width;
	int testcase_query = 0;
    int i;

	if (read_image(&height, &width, &image) == 1){
		return 1;
	}
   
    printf("Input number of query : ");
	if(scanf("%d", &testcase_query) != 1){
        printf("!ERROR! : That is not a valid choice\n");
        while(1){
            if(getchar() == '\n'){
                break;
            }
        }
        return 1;
    }
    //if testcase_query is not a number, throw error and empty buffer

	for(i = 0; i < testcase_query; i++){
		run_query(&height, &width, &image);
	}	

    free_canvas(height, image);

    return 0;
}

int read_image(int *height, int *width, char*** image_address){
    //declare image and dynamically allocate it with function make_board
    //get character and fill image with get_character
    char** image;
    int error_type;
    //error_type is a int-type var which contains types of error that
    //get_character has returned

	printf("Input height, width : ");
	scanf("%d%d", height, width);
	
	if(check_size(*height, *width) == 1){
		printf("!ERROR! : Your canvas cannot be bigger than 4096 * 4096.\n");
		return 1;
	}
    //when height or width is bigger than 4096, throw error

	image = make_board(image, *height, *width);

	printf("Input the image :\n");
    error_type = get_character(&image, *height, *width);
	if(error_type == 1){
		printf("!ERROR! : Your image is bigger than your canvas.\n");
		return 1;
	}
    //when typed string is longer than width, throw error

    if(error_type == 2){
        printf("!ERROR! : Your image is smaller than your canvas.\n");
        return 1;
    }
    //when typed string is shorter than width, throw error

    *image_address = image;
	return 0;
}

int check_size(int height, int width){
    //check canvas's size with height, width and throw error when they exceed 4096
	if(height > 4096 || width > 4096){
		return 1;
	}
	return 0;
}

char** make_board(char** image, int height, int width){
   //dinamically allocate image whith height and width
    int i;

	image = (char**)malloc(height*sizeof(char*));

	for(i = 0; i < height; i++){
		image[i] = (char*)malloc(width*sizeof(char));
	}

	return image;
}

int get_character(char*** image, int height, int width){
    //get character and save it at temp
    //check if error and if not, save it at image;

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
                //if typed string is longer than width, throw error
			}
            if(j != width && temp == '\n'){
                return 2;
                //if typed string is shorter that width, throw error
            }

			temp_image[i][j] = temp;
		}
	}

	return 0;
}

int run_query (int *height, int *width, char*** image){
	//get query number and run each run_query functions
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
        //if query is not a number between 1 to 5, throw error
	}

	return 0;
}

int run_query_1(int *height, int *width, char*** image){
    //get option and run resize, print result
    int option, temp;
    
    printf("\nResize\n");
    printf("Input 0 or 1 : ");
    scanf("%d", &option);
    
    if(option != 0 && option != 1){
        printf("!ERROR! : That is not a valid choice.\n");
        print_image(*height, *width,  *image);
        return 1;
    }
    //if option is neither 0 nor 1, throw error

    temp = *height;

    *image = resize(option, height, width, *image);

    if(temp == *height){
        print_image(*height, *width,  *image);
        return 1;
    }
    //if temp == height, it means there was error and image wasn't resized
    //so print image and return error

    printf("Result_resize height : %d, width : %d\n",*height, *width);
    print_image(*height, *width,  *image);

    return 0;
}

int run_query_2(int *height, int *width, char*** image){
    int option;
    //get option and run rotate, print result
    printf("\nRotate\n");
    printf("Input 0 or 1 or 2 : ");
    scanf("%d", &option);
    
    if(option != 0 && option != 1 && option != 2){
        printf("!ERROR! : That is not a valid choice.\n");
        print_image(*height, *width,  *image);
        return 1;
    }
    //if option is not 0, nor 1, nor 2, then throw error

    *image = rotate(height, width, option, *image);

    printf("Result_rotate height : %d, width : %d\n",*height, *width);
    print_image(*height, *width,  *image);

    return 0;
}

int run_query_3(int *height, int *width, char*** image){
    //get option and run flip, print result
    int option;

    printf("\nFlip\n");
    printf("Input 0 or 1 : ");
    scanf("%d", &option);
    
    if(option != 0 && option != 1){
        printf("!ERROR! : That is not a valid choice.\n");
        print_image(*height, *width,  *image);
        return 1;
    }
    //if option is neither 0, nor 1, then throw error

    flip(*height, *width, option, image);
    
    print_image(*height, *width,  *image);

    return 0;
}

int run_query_4(int *height, int *width, char*** image){
    //TODO modify temp
    //get coordinates, options, and run copy, paste, print result
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
    //if the coordinates are smaller than 0 or bigger then hiehgt and width,
    //throw error 

    if(c_h < 1 || c_w < 1){
        printf("!ERROR! : Your copy area is too small.\n");
        print_image(*height, *width, *image);
        return 1;
    }
    //when c_h or c_w is smaller than 1, throw error

    if(c_h > 4096 || c_w > 4096){
        printf("!ERROR! : Your copy area is too big.\n");
        print_image(*height, *width, *image);
        return 1;
    }
    //when c_h or c_w is bigger than 4096, throw error

    temp = copy(x1, y1, c_h, c_w, *height, *width, *image);
    paste(x2, y2, *height, *width, *image, temp);

    print_image(*height, *width,  *image);
    
    return 0;
}

int run_query_5(int *height, int *width, char*** image){
    //get coordiates, color and run fill, print result
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
    //if typed coordinates exceed image, throw error
    if((*image)[x][y] == color){
        printf("!ERROR! : That is not a valid color.\n");
        print_image(*height, *width, *image);
        return 1;
    }
    //if typed color is same with curren color, trow error

    *image = fill(x, y, color, *height, *width, *image);

    print_image(*height, *width, *image);

    return 0;
}

char** resize(int arg1, int* height, int* width, char** image){
    //using option from run_query_1(which is saved in arg1), resize image
	char** result_image;
    int i, j;

    if(arg1 == 0){
        if(check_size(*height * 2, *width * 2) == 1){
            printf("!ERROR! : Your image is too big to expand.\n");
            return image;
        }
        //if size of image after resize is bigger than 4096*4096, return
        //original image

        result_image = make_board(result_image, *height * 2, *width * 2);

        for(i = 0; i < *height; i++){
            for(j = 0; j < *width; j++){
                result_image[2 * i][2 * j] = (image)[i][j];
                result_image[2 * i + 1][2 * j] = (image)[i][j];
                result_image[2 * i][2 * j + 1] = (image)[i][j];
                result_image[2 * i + 1][2 * j + 1] = (image)[i][j];
            }
        }
        //dinamically allocate result_image and fill it in with original image's
        //values

        free_canvas(*height, image);
        *height = *height * 2;
        *width = *width * 2;
        //free image and modify height and width

        return result_image;
    }
    if(arg1 == 1){
        if(*height == 1 || *width == 1){
            printf("!ERROR! : Your image is too small to down-size.\n");
            return image;
        }
        //if size of image is 1*1, return original image

        result_image = make_board(result_image, *height / 2, *width / 2);

        for(i = 0; i < *height / 2; i++){
            for(j = 0; j < *width / 2; j++){
                result_image[i][j] = (image[2 * i][2 * j]
                                    + image[2 * i + 1][2 * j]
                                    + image[2 * i][2 * j + 1]
                                    + image[2 * i + 1][2 * j + 1]) / 4;
            }
        }
        //dinamically allocate result_image and fill it in with averages of
        //original image's values

        free_canvas(*height, image);
        *height = *height / 2;
        *width = *width / 2;
        //free image and modify height and width

        return result_image;
    }
}

char** rotate(int *height, int *width, int angle, char** image){
    //using option from run_query_2(which is saved in angle), rotate image
    char** result_image;
    int temp, count, i , j;
    result_image = make_board(result_image, *height, *width);
    //make result_image and dinamically allocate it

    for(count = 0; count <= angle; count++){
        result_image = realloc_canvas(*width, *height, result_image);
        //realloc result_image

		for(i = 0; i < *height; i++){
			for(j = 0; j < *width; j++){
				result_image[j][*height - 1 - i] = image[i][j];
			}
		}
        //fill in result_image using original image's values

		free_canvas(*height, image);
		
		temp = *height;
		*height = *width;
		*width = temp;
		//free imgae and modify height and width

		image = result_image;

        if (count != angle) {
            result_image = make_board(result_image, *height, *width);
        }
	}

	return image;
}

void flip(int height, int width, int flag, char*** image){
    //using option from run_query_3(which is saved in flag), flip image
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
    //swap values using function swap
}

char* copy(int x1, int y1, int c_h, int c_w, int height, int width, char** image){
    //using coordinates and sizes from run_query_4(which is saved in x1, y1,
    //c_h, c_w), copy values from image and save it to temp
    int x_end, y_end, count = 0;
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
    //declare int-type var named x_end and y_end, and save last coordinates of
    //copy area to x_end and y_end

    temp = malloc(((x_end - x1 + 2)*(y_end  - y_end + 1) + 1) * sizeof(char));
    //dinamically allocate temp using acquired copy area

    for(i = y1; i <= y_end; i++){
        for(j = x1; j <= x_end; j++){
            temp[count] = image[i][j];
            count++;
        }
        temp[count] = '\0';
        count++;
    }
    temp[count] = '\0';
    //fill temp with values in copy area and at every end of a line, add '\0'

    return temp;
}

void paste(int x2, int y2, int height, int width, char** image, char* temp){
    //using coordinates from run_query_4 and temp, paste copied area to image
    int i = y2, j = x2, count = 0;

    while(1){
        if(i >= height){
            break;
        }
        //if i >= height, the coordinate exceeds images so break
        if(temp[count] == '\0'){
            break;
        }
        //if temp[count] == 0, it means there are two '\0' in a row and that is
        //the end of temp so break
        while(1){
            if(temp[count] == '\0'){
                count++;
                j = x2;
                break;
            }
            //if temp[count] == 0, it means that it's end of a line of a copy
            //area so initialize j as x2 and break
            if(j >= width){
                 j = x2;
                 while(1){
                    if(temp[count] == '\0'){
                        break;
                    }
                    count++;
                 }
                 count++;
                break;
            }
            //if j >= width, the coordinate exceeds image so initialize j as x2, find
            //another start of a copy area's line (which is the next value of
            //closest '\0') then break
            image[i][j] = temp[count];
            //paste value of temp to image
            j++;
            count++;
        }
        i++;
    }

    free(temp);
}

char** fill(int x, int y, char color, int height, int width, char** image){
    //using coordinate and color from run_query_5, search adjacent values and
    //fill them with saved color
    int size = 1, count = 0;
    char check;

    struct coordinate *queue = malloc(size * sizeof(struct coordinate));

    check = image[x][y];

    queue[count].x = x;
    queue[count].y = y;
    //make array of structures which contains coordinate x, y and save given
    //coordinate x, y at first index 

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
        //search adjacent coordinates and if their value is same with original
        //pixel, expand queue and save the coordinate at the queue
        //change original pixel's color to given color
    }
    printf("Number of colored pixels = %d\n",size);
    
    free(queue);

    return image;
}

void swap(char* ch1, char* ch2){
    //swap characters
    char temp;

    temp = *ch1;
    *ch1 = *ch2;
    *ch2 = temp;
}

void free_canvas(int height, char** image){
    //free canvas with height
    int i;

    for(i = 0; i < height; i++){
        free(image[i]);
    }
    free(image);
}

char** realloc_canvas(int height, int width, char** image){
    //realloc_canvas with height and width
    //height is result image's height and prev_height is height of image before realloc
    int prev_height = width;
    int prev_width = height;
    int i;

    int min_height = prev_height < height ? prev_height : height;
    for (i = height; i < prev_height; ++i)
        free(image[i]);
    //if height < prev_height, free image[height] to image[print_height - 1]

    image = realloc(image, height * sizeof(char*));
    //realloc image using height
    for (i = 0; i < min_height; i ++) {
		image[i] = realloc(image[i], width*sizeof(char));
    }
    //realloc image[] using min_height, which is smaller value between height
    //and prev height
    for (i = min_height; i < height; i ++) {
        image[i] = malloc(width * sizeof(char));
    }
    //malloc image[i] from i = min_height to height

    return image;
}

void print_image(int height, int width, char** image){
    //print image with height and width
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
    //expand queue and modify size
    *size += 1;
    queue = realloc(queue, *size * sizeof(struct coordinate));

    return queue;
}
