#include <stdio.h>
#include <stdlib.h>



typedef struct {
    int marked;
} Object;

typedef struct {
    Object** objects;
    int capacity;
    int count;
    int threshold;
} GarbageCollector;


void gc_init(GarbageCollector* gc, int threshold) {
    gc->objects = malloc(sizeof(Object*) * threshold);
    gc->capacity = threshold;
    gc->count = 0;
    gc->threshold = threshold;
}

// Create a new object
Object* gc_new_object(GarbageCollector* gc) {
    Object* object = malloc(sizeof(Object));
    object->marked = 0;

    if (gc->count == gc->capacity) {
        gc->capacity *= 2;
        gc->objects = realloc(gc->objects, sizeof(Object*) * gc->capacity);
    }

    gc->objects[gc->count++] = object;

    return object;
}

void gc_mark(Object* object) {
    if (object == NULL || object->marked) {
        return;
    }

    object->marked = 1;

    // Mark any referenced objects here
}



void gc_sweep(GarbageCollector* gc) {
    for (int i = 0; i < gc->count; i++) {
        if (!gc->objects[i]->marked) {
            free(gc->objects[i]);
            gc->objects[i] = NULL;
        } else {
            gc->objects[i]->marked = 0;
        }
    }
}

void gc_collect(GarbageCollector* gc) {
    gc_mark_root_objects(gc);
    gc_sweep(gc);
}


void gc_cleanup(GarbageCollector* gc) {
    for (int i = 0; i < gc->count; i++) {
        free(gc->objects[i]);
    }
    free(gc->objects);
}

int main() {
    GarbageCollector gc;
    gc_init(&gc, 16);
    Object* obj1 = gc_new_object(&gc);
    Object* obj2 = gc_new_object(&gc);
    gc_collect(&gc);
    gc_cleanup(&gc);
    return 0;
}
