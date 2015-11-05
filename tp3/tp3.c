/***********************************
 * Auteur  : Alain Fourmigue
 * Projet  : INF1600 TP3
 * Contenu : Programme de test
 * Date    : Fevrier 2014
 ***********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/********************************************************************/
static void parse(char*,float*,float*,int,int,int);
static float max_diff(float*,float*,int);
static void convert_to_fixed_point(float*,int*,int);
static void convert_to_float(int*,float*,int);

static float dot_ref(float*,float*,int);
static void mac_ref(float*,float*,float,float*,int);
static void mul_ref(float*,float*,float*,int,int,int);

extern int dot(int*,int*,int);
extern void mac(int*,int*,int,int*,int);
extern void mul(int*,int*,int*,int,int,int);

/********************************************************************/
int main(int argc,char** argv){

  float *a,*b,*x,*y,r,s,f;
  int *c,*d,*u,v,e;
  int p,q,n;

  // Taille du probleme modele
  p=9;
  q=117;
  n=1521;

  // allocation de memoire pour stocker les coefficients du probleme
  a=(float*)calloc(4*n,sizeof(float));
  b=(float*)calloc(n,sizeof(float));
  x=(float*)calloc(n,sizeof(float));
  y=(float*)calloc(n,sizeof(float));

  c=(int*)calloc(4*n,sizeof(int));
  d=(int*)calloc(n,sizeof(int));
  u=(int*)calloc(n,sizeof(int));

  // lecture des coefficients du probleme modele
  parse("problem.txt",a,b,p,q,n); 

  // conversion en virgule fixe
  convert_to_fixed_point(a,c,4*n);
  convert_to_fixed_point(b,d,n);
  convert_to_float(c,a,4*n);
  convert_to_float(d,b,n);

  // comparaison avec la fonction dot de reference
  r=dot_ref(b,b,n);
  v=dot(d,d,n);
  convert_to_float(&v,&s,1);
  printf("Fonction 'dot': difference=%.3e (devrait etre < 1e-6)\n",fabsf(r-s));

  // comparaison avec la fonction mul de reference
  mul_ref(x,a,b,p,q,n);
  mul(u,c,d,p,q,n);
  convert_to_float(u,y,n);
  printf("Fonction 'mul': difference=%.3e (devrait etre < 1e-6)\n",max_diff(x,y,n));

  // comparaison avec la fonction mac de reference
  f=0.25;
  convert_to_fixed_point(&f,&e,1);
  mac_ref(x,b,f,b,n);
  mac(u,d,e,d,n);
  convert_to_float(u,y,n);
  printf("Fonction 'mac': difference=%.3e (devrait etre < 1e-6)\n",max_diff(x,y,n));

  // liberation de la memoire allouee
  free(a);
  free(b);
  free(x);
  free(y);

  free(c);
  free(d);
  free(u);

  return 0;
}

/*******************************************************************/
static float dot_ref(float *u,float *v,int n){

  int i;
  float sum=0;
  for(i=0; i<n; i++)
    sum+=u[i]*v[i];  
  return sum;
}

/*******************************************************************/
static void mac_ref(float *a,float *b,float f,float *c,int n){

  int i;
  for(i=0; i<n; i++)
    a[i]=b[i]+f*c[i];  
  return;
}

/********************************************************************/
static void mul_ref(float *y,float *a,float *x,int p,int q,int n){

  int i;
  float *m,*b,*w,*s;

  m=a;
  b=a+n;
  w=a+2*n;
  s=a+3*n;

  for(i=0; i<n; i++){

    y[i]=m[i]*x[i];

    if(i>=1)
      y[i]+=b[i]*x[i-1];

    if(i<n-1)
      y[i]+=b[i+1]*x[i+1];

    if(i>=p)
      y[i]+=w[i]*x[i-p];

    if(i<n-p)
      y[i]+=w[i+p]*x[i+p];

    if(i>=q)
      y[i]+=s[i]*x[i-q];

    if(i<n-q)
      y[i]+=s[i+q]*x[i+q];
  }

  return;
}

#define FRACTION 0x100000

/********************************************************************/
static void convert_to_fixed_point(float *x,int *u,int n){

  int i;
  for(i=0; i<n; i++)
    u[i]=(int)(x[i]*FRACTION);
  return;
}

/********************************************************************/
static void convert_to_float(int *u,float *x,int n){

  int i;
  for(i=0; i<n; i++){
    x[i]=(float)u[i];
    x[i]/=FRACTION;
  }
  return;
}

/********************************************************************/
static float max_diff(float *x,float *y,int n){

  int i;
  float max=0;
  for(i=0; i<n; i++)
    max=fmaxf(max,fabsf(x[i]-y[i]));
  return max;
}

/********************************************************************/
static void parse(char *path,float *a,float *b,int p,int q,int n){

  FILE *file;
  char buffer[256],*end;
  int i=0;

  file=fopen(path,"r");
  if(!file){
    fprintf(stderr,"failed to open file '%s'\n",path);
    exit(-1);
  }

  printf("Parsing file '%s'...\n",path);

  while(fgets(buffer,256,file)){
    if(strlen(buffer)>1 && buffer[0]!='%'){

      if(i>=n){
        fprintf(stderr,"error: parsed too many values....\n");
        exit(-1);
      }

      a[i]=strtod(buffer,&end);
      a[i+n]=strtod(end,&end);
      a[i+2*n]=strtod(end,&end);
      a[i+3*n]=strtod(end,&end);
      b[i]=strtod(end,&end);
      i++;
    }
  }
  
  fclose(file);
  return;
}
