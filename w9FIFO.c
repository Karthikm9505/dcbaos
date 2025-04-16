#include<stdio.h>
#include<stdlib.h>

int isPagePresent(int frames[], int num_frames, int page)
{
    for(int i = 0; i < num_frames; i++)
    {
        if(frames[i] == page)
        {
            return 1;
        }
    }
    return 0;
}

void fifoPageReplacement(int pages[], int num_pages, int num_frames)
{
    int frames[num_frames];
    int page_faults = 0;
    int next_frame_to_replace = 0;
    for(int i = 0; i < num_frames; i++)
    {
        frames[i] = -1;
    }
    printf("Page Reference String");
    for(int i = 0; i < num_pages; i++)
    {
        printf("%d", pages[i]);
    }
    printf("\n\n");
    printf("Step\tPage\tFrames\t\tPage Fault\n");
    printf("-----------------\n");
    for(int i = 0; i < num_pages; i++)
    {
        int current_page = pages[i];
        printf("%d\t%d\t", i + 1, current_page);
        if(!isPagePresent(frames, num_frames, current_page))
        {
            frames[next_frame_to_replace] = current_page;
            next_frame_to_replace = (next_frame_to_replace + 1) % num_frames;
            page_faults++;
            for(int j = 0; j < num_frames; j++)
            {
                if(frames[j] != -1)
                {
                    printf("%d", frames[j]);
                }
                else
                {
                    printf("- ");
                }
            }
            printf("\t\tYes\n");
        }
        else
        {
            for(int j = 0; j < num_frames; j++)
            {
                if(frames[j] != -1)
                {
                    printf("%d", frames[j]);
                }
                else
                {
                    printf("- ");
                }
            }
            printf("\t\tNo\n");
        }
    }
    printf("\nTotal Page Faults %d\n", page_faults);
    printf("Page Fault Rate %.2f%%\n", (float)page_faults / num_pages * 100);
}

int main()
{
    int num_pages, num_frames;
    printf("Enter the no.of pages in the Reference String\n");
    scanf("%d", &num_pages);
    int pages[num_pages];
    printf("Enter the Page Reference String\n");
    for(int i = 0; i < num_pages; i++)
    {
        scanf("%d", &pages[i]);
    }
    printf("Enter the no.of frames");
    scanf("%d", &num_frames);
    fifoPageReplacement(pages, num_pages, num_frames);
    return 0;
}
