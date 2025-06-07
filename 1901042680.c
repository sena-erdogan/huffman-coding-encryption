#include<stdio.h>
#include<stdlib.h>

typedef struct tree_s{

	char data;

	int bin, count;

	struct tree_s *left, *right;

}tree;

typedef struct ll_s{

	char data;

	int count;

	struct ll_s *next, *prev;

}ll;

int is_in_ll( ll *head, char new );

void insert_at_end( ll *head, char new );

void increment( ll *head, char new );

int sum_ll( ll *head );

int node_count(ll *head);

void sort_ll(ll *head);

void huffman(ll *head, tree *root);

void decode_huffman(tree *root, char *infile, char *outfile);

void encode_huffman(tree *root, char *infile, char *outfile);

int traverse(tree *root, char dat);

void en_de_code(ll *head);

int is_in_ll( ll *head, char new ){

	if( head->next == NULL ){

		if( head->data == new )	return 1;

	}else{

		while( head->next != NULL ){

			if( head->data == new )	return 1;

			head = head->next;

		}

	}

	return 0;

}

void insert_at_end( ll *head, char new ){

	while( head->next != NULL ){

		head = head->next;

	}

	head->next = (ll*)malloc(sizeof(ll));

	head->data = new;
	head->count += 1;
	head->next->next = NULL;

}

void increment( ll *head, char new ){

	while( head->data != new ){

		head = head->next;

	}

	head->count += 1;

}

int sum_ll( ll *head ){

	int sum=0;

	while( head->next != NULL ){

		sum += head->count;

		head = head->next;

	}

	return sum;

}

int node_count(ll *head){

	int count=0;

	while( head->next != NULL ){

		count++;

		head = head->next;

	}

	return count;

}

void sort_ll(ll *head){

	ll *curr, *n;
	int i, j;
	int tempcount;
	char tempdata;

	for( i = node_count(head) - 2; i>=0;i-- ){

		curr = head;
		n = curr->next;

		for( j = 0; j <= i; j++ ){

			if(curr->count > n->count){

				tempdata = curr->data;
				tempcount = curr->count;
				curr->data = n->data;
				curr->count = n->count;
				n->data = tempdata;
				n->count = tempcount;

			}

			curr = n;
			n = n->next;

		}

	}

}

void huffman(ll *head, tree *root){

	int sum;
	tree *nroot;

	while( head->next != NULL ){

		ll *p;
		p = head;

		nroot = (tree*)malloc(sizeof(tree));
		nroot->left->data = head->data;
		nroot->right->data = head->next->data;
		nroot->count = head->count + head->next->count;

		if( root->left != NULL )	root->right = nroot;
		else						root->left = nroot;
		

		head = head->prev;
		sort_ll(head);
		free(p);

	}

}


int traverse(tree *root, char dat){

	if( root != NULL ){

		if( root->data == dat )	return 1;

		if( traverse(root->left, dat) || traverse(root->right, dat) )
			return ( root->bin );

	}

	return -1;

}

void decode_huffman(tree *root, char *infile, char *outfile){

	int b;

	FILE *inp, *outp;
	inp = fopen(infile,"rt");
	outp = fopen(outfile,"wt");

	tree *p = root;

	while( !feof(inp) ){

		while( p->left != NULL || p->right != NULL ){

			b = fgetc(inp);

			if( b == 0 )		p = p->left;
			else if( b == 1 )	p = p->right;

		}

		fputc(p->data, outp);

		p = root;

	}

}

void encode_huffman(tree *root, char *infile, char *outfile){

	int code[50], i;
	char dat;

	FILE *inp, *outp;
	inp = fopen(infile,"rt");
	outp = fopen(outfile,"wt");

	while(!feof(inp)){

		i=0;

		dat = fgetc(inp);

		while( traverse(root, dat) != -1 ){

			code[i] = traverse(root, dat);
			i++;

		}

		fwrite(code, sizeof(int), 50, outp);

	}

}

void print_ll(ll *head){

	while( head->next != NULL ){

		printf("%c %d\n", head->data, head->count);

		head = head->next;

	}

}

void print_tree(tree *root){

	if( root != NULL ){

		print_tree(root->left);
		print_tree(root->right);

	}

}

void en_de_code(ll *head){

	int bcb = 0, bca = 0;/* bcb (bit count before compressing) & bca (bit count after compressing) */

	tree *root;

	huffman(head, root);

	encode_huffman(root, "message.txt", "encoded.dat");

	decode_huffman(root, "encoded.dat", "decoded.txt");

	FILE *inp;

	inp = fopen("decoded.txt","rt");

	while(!feof(inp)){

		fgetc(inp);
		bcb++;

	}

	fclose(inp);

	printf("Size of your text before compressing: %d\n\n", 8 * bcb);

	inp = fopen("encoded.dat","rt");

	while(!feof(inp)){

		fgetc(inp);
		bca++;

	}

	fclose(inp);

	printf("Size of your text after compressing: %d\n\n", bca);

	printf("Size difference between encryption and decryption: %d\n\n", (8 * bcb) - bca);


}

void main(){

	char new;

	ll *head;
	head->next = NULL;
	head->prev = NULL;

	FILE *inp;
	inp = fopen("reference.txt","rt");

	while( !feof(inp) ){

		new = fgetc(inp);

		if( is_in_ll(head, new) != 1 ){

			insert_at_end(head, new);

		}else{

			increment(head, new);

		}

	}

	fclose(inp);

	printf("\nBefore sorting: \n\n");

	print_ll(head);

	sort_ll(head);

	printf("\nAfter sorting: \n\n");

	print_ll(head);
	printf("\n\n");

	en_de_code(head);

}