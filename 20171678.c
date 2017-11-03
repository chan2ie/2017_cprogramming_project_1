#include <stdio.h>
#include <stdlib.h>

int run_function();
int read_image(char** image);
int check_size(int height, int width);
char** make_board(char** image, int height, int width);
int get_character(char** image, int height, int width);
int run_query(char** image);
void print_image(int height, int width, char** image);
char** resize(int arg1, int* height, int* width, char** image);
char** rotate(int* height, int* width, int angle, char** image);
void flip(int height, int width, int flag, char** image);
char* copy(int x1, int y1, int c_h, int c_w, int height, int width, char** image);
void paste(int x2, int y2, int height, int width, char** image, char* temp);

int main(){
	int testcase;

	printf("Input testcase : ");
	scanf("%d", &testcase);

	for(int i = 0; i < testcase; i++){
		run_function();
	}

	return 0;
}

int run_function(){
	char** image;
	int testcase_query;

	if (read_image(image) == 1){
		return 1;
	}

	printf("Input number of query : ");
	scanf("%d", &testcase_query);

	for(int i = 0; i < testcase_query; i++){
		run_query(image);
	}
}

int read_image(char** image){
	int height, width;
	printf("Input height, width : ");
	scanf("%d%d", &height, &width);
		
	if(check_size(height, width) == 1){
		printf("!ERROR! : Your canvas cannot be bigger than 4096 * 4096.\n");
		return 1;
	}

	image = make_board(image, height, width);

	printf("Input the image :\n");
	if(get_character(image, height, width) == 1){
		printf("!ERROR! : Your image is bigger than your canvas.\n");
		return 1;
	}

	return 0;
}

int check_size(int height, int width){

	if(height > 4096 || width > 4096){
		return 1;
	}
	return 0;
}

char** make_board(char** image, int height, int width){

	image = (char**)malloc(height*sizeof(char*));

	for(int i = 0; i < height; i++){
		image[i] = (char*)malloc(width*sizeof(char));
	}

	return image;
}

int get_character(char** image, int height, int width){
	char temp;

	getchar();

	for(int i = 0; i < height; i++){
		for(int j = 0; j < width + 3; j++){
			scanf("%c", &temp);
			if(j == width && temp == '\n'){
				break;
			}
			if(j == width && temp != '\n'){
				return 1;
			}

			image[i][j] = temp;
		}
	}

	return 0;
}

int run_query(char** image){
	int which_query;

	printf("Input query :");
	scanf("%d", &which_query);
	
	switch(which_query){
		case 1 : 
			image = resize(0, height, width, image);
			print_image(height, width, image);
			break;
		case 2 :
			break;
		case 3 :
			break;
		case 4 :
			break;
		case 5 : 
			break;

		default :
			printf("!ERROR! : That is not a valid choice.\n");
	}

	return 0;
}

char** resize(int arg1, int* height, int* width, char** image){
	
}

void print_image(int height, int width, char** image){
	printf("Result Image\n\n");

	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			printf("%c",image[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
