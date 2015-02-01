#ifndef __project2__artifacts__
#define __project2__artifacts__

struct Artifact {
    int points;
    int weight;
};

void read_artifacts(Artifact *artifacts, std::size_t size);

#endif /* defined(__project2__artifacts__) */
