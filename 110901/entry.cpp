#include <cstdio>
#include <cstdlib>
#include <cstring>
#pragma warning(disable:4996)
#pragma pack(1)

struct sound
{
    char f;
    char m;
};

unsigned int frefromsound(sound s)
{
    int p = 1;
loops:
    static unsigned int low[] = {262, 294, 330, 349, 392, 440, 494};
    if (1 == s.f)
    {
        return p * low[s.m - 1];
    }
    else
    {
        s.f -= 1;
        p *= 2;
        goto loops;
    }
}

int main(int argc, char* argv[])
{
    FILE * fp;

    if (1 == argc)
    {
        printf("��������!\n");
        printf("�������� /? ��ȡ����\n");
        system("pause>nul");
        return 1;
    }
    else if (2 == argc)
    {
        if (0 == (strcmp(argv[1], "/?")) || 0 == strcmp(argv[1], "\\?"))
        {
            printf("\n\n");
            printf("����: /default|/?|FileName");
            printf("\n\n");
            printf("      ���ļ���Ϊ FileName ���ĵ�����ָ�����򲥷�����");
            printf("\n");
            printf("      /?        -  �򿪰���ҳ��\n");
            printf("      /default  -  ��ȡĬ���ļ�: myfavarite.dat\n\n\n");
            printf("        developed by Yuan     \n\n\n");
            system("pause>nul");
            return 1;
        }
        else if ((0 == strcmp(argv[1], "/default")) || 0 == strcmp(argv[1], "\\default"))
        {
            fp = fopen("myfavarite.dat", "rb");
        }
        else if ((0 == strcmp(argv[1], "�²�")))
        {
            printf("˭֪����ʦ�����������ҵ\n");
            printf("һ���ļ�, �ѵ���Ӧ��ǰ�����ַ��Ǳ�ʶ������?!\n");
            printf("ͬһ�����ڵ���Ϣ��Ȼ������һ��\n");
            printf("����˵������<<�׺�һ��Ц>>, ���������˼���û������=_=!\n");
            printf("�Ҿ�����ʦ��������仰��, ��ʦӦ��û��Ȥ������ҵĶ����Ŷ�\n");
            printf("��л�㿴����仰!\n");
            system("pause>nul");
            return 233;
        }
        else
        {
            fp = fopen(argv[1], "rb");
        }
    }
    else
    {
        printf("��������, ������!\n\n");
        system("pause>nul");
        return 3;
    }
        
    if (nullptr == fp)
    {
        printf("error!\n\n");
        system("pause>nul");
        return -1;
    }
    int d[2];
    int &n = d[0], &t = d[1];
    fread(d, sizeof(int), 2, fp);
    sound* ps;
    ps = static_cast<sound*>(malloc(n * sizeof(sound)));
    if (nullptr == ps)
    {
        printf("memory error\n");
        fclose(fp);
        system("pause>nul");
        return -2;
    }
    fread(ps, sizeof(sound), n, fp);
    unsigned char * pl;
    pl = static_cast<unsigned char*>(malloc(n * sizeof(unsigned char)));
    if (nullptr == pl)
    {
        printf("memory error\n");
        fclose(fp);
        free(ps);
        system("pause>nul");
        return -2;
    }
    fread(pl, sizeof(unsigned char), n, fp);
    fclose(fp);
    for (int i = 0; i < n; i++)
    {
        int k = frefromsound(ps[i]);
        _beep(k, t * static_cast<unsigned int>(pl[i]));
    }
    free(ps);
    free(pl);
    system("pause");
    return 0;
}