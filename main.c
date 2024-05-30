#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b, int c)
{
    if (a < b && a < c) return a;
    if (b < a && b < c) return b;
    return c;
}

int minEditDistance(char *str1, char *str2)
{
    int len1=strlen(str1);
    int len2=strlen(str2);

    int **dp=(int **)malloc((len1+1)*sizeof(int *));

    for (int i=0;i<=len1;i++){
        dp[i]=(int *)malloc((len2+1)*sizeof(int));
    }

    for (int i=0;i<=len1;i++){
        for (int j=0;j<=len2;j++){
            if (i==0) {
                dp[i][j]=j;
            }
            else if (j==0){
                dp[i][j]=i;
            }
            else if (str1[i-1]==str2[j-1]){
                dp[i][j]=dp[i-1][j-1];
            }
            else{
                dp[i][j]=1+min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1]);
            }
        }
    }
    int result = dp[len1][len2];
    for (int i = 0; i <= len1; i++){
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    FILE *file1,*file2;
    char rule[100],syntax[100];
    char str1[1000],str2[1000];
    int minOps;
    printf("Enter filename 1: ");
    scanf("%s",rule);
    printf("Enter filename 2: ");
    scanf("%s",syntax);
    file1 = fopen("rule.in","r");
    file2 = fopen("syntax.in","r");
    if (file1==NULL || file2==NULL){
        printf("Error opening files.\n");
        return 1;
    }
    fgets(str1,sizeof(str1),file1);
    fgets(str2,sizeof(str2),file2);
    strtok(str1,"\n");
    strtok(str2,"\n");
    fclose(file1);
    fclose(file2);
    minOps=minEditDistance(str1,str2);
    printf("Minimum operations required: %d\n",minOps);
    return 0;
}
