#include <bits/stdc++.h>

using namespace std;

#define ll  long long int
#define ld long double

struct image
{
    int id1;
    int id2;
    int number_of_tags;
    vector<string>tags;
    unordered_map<string, bool> exist_tags;
};

vector<image>vertical_images, horizontal_images;

vector<image>shuffle_images(vector<image> imgs)
{
      unsigned seed = chrono::system_clock::now().time_since_epoch().count();
      shuffle (imgs.begin(), imgs.end(), default_random_engine(seed));
      return imgs;
}


image merge_images(image img1, image img2)
{
    for(auto it=img2.exist_tags.begin(); it!=img2.exist_tags.end(); it++)
        if(!img1.exist_tags[it->first])
            img1.exist_tags[it->first] = 1, img1.tags.push_back(it->first);

    image new_image={img1.id1, img2.id1, img1.tags.size(), img1.tags, img1.exist_tags };
    return new_image;
}


int compare_images(image slide_right, image slide_left)
{
    int right_only, left_only, common;

    common = 0;
    right_only = slide_right.exist_tags.size();
    left_only = slide_left.exist_tags.size();

    for(auto it=slide_right.exist_tags.begin(); it!=slide_right.exist_tags.end(); it++)
        if(slide_left.exist_tags[it->first])
            common++;
    right_only-=common;
    left_only-=common;
    return min(common, min(right_only, left_only));
}

void rank_images(vector<image>&horizontal_images)
{
    for(int i=0; i<horizontal_images.size() - 1; i++)
    {
        int best = i;
        int score = 0;
        for(int j=i+1, k=0; k<100 &&  j<horizontal_images.size(); j++, k++)
        {
            int compare = compare_images(horizontal_images[i], horizontal_images[j]);
            if(compare>score)
                score = compare, best=j;
        }
        swap(horizontal_images[best], horizontal_images[i+1]);
    }
}

void merge_vertical()
{
    if(vertical_images.size()<2)
        return;
    vertical_images = shuffle_images(vertical_images);
    rank_images(vertical_images);
    for(int i=0; i<vertical_images.size()-1; i+=2)
    {
        horizontal_images.push_back(merge_images(vertical_images[i], vertical_images[i+1]));
    }

}


int main()
{
	ios::sync_with_stdio(false);
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	// Read and Write Files - change the file name for different test data
	freopen("in/e.txt", "r", stdin);
	freopen("out/e.txt", "w", stdout);
    int n;
    cin>>n;
    // Input
    for(int i=0; i<n; i++)
        {
            int number_of_tags;
            char position;
            unordered_map<string, bool>exist_tags;

            cin>>position;
            cin>>number_of_tags;
            vector<string>tags(number_of_tags);

            for(int j=0; j<number_of_tags; j++)
                cin>>tags[j], exist_tags[tags[j]]=1;

            if(position == 'H')
                horizontal_images.push_back({i, -1, number_of_tags, tags, exist_tags});
            else
                vertical_images.push_back({i, -1, number_of_tags, tags, exist_tags});
        }
    // Merge vertical images; so we only have horizontal images (slides)
    merge_vertical();
    // Shaffle and rank horizontal images
    horizontal_images = shuffle_images(horizontal_images);
    rank_images(horizontal_images);

    cout<<horizontal_images.size()<<endl;
    for(int i=0; i<horizontal_images.size(); i++)
    {
        cout<<horizontal_images[i].id1;
        if(horizontal_images[i].id2 !=-1 )
            cout<<" "<< horizontal_images[i].id2;
        cout<<endl;
    }
	return 0;
}

