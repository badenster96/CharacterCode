#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cctype>
#include <iostream>
#include <algorithm>

#include "_3DModelLoader.h"
#include "TextureLoader.h"

// Table of precalculated normals
// CHANGED: from vec3_t to vec3
static const vec3 anorms_table[162] = {
    #include "External/Anorms.h"
    // This assumes Anorms.h contains data like {x, y, z}, {x, y, z}, ...
    // which can initialize both float[3] and vec3
};

_3DModelLoader::_3DModelLoader()
{
    pos.x = 0.0;
    pos.y = 0.0;
    pos.z = 0.0;

    rotateX = 0.0;
    rotateY = 0.0;
    rotateZ = 0.0;
    scale = 1.0;

    animStandStart = 0;
    animStandEnd = 39;
    animWalkStart = 40;
    animWalkEnd = 45;

    currentAnimStart = animStandStart;
    currentAnimEnd = animStandEnd;
    currentFrame = animStandStart;
    interp = 0.0f;
    lastTime = 0.0;

    myTex = new TextureLoader();
}

_3DModelLoader::~_3DModelLoader()
{
    FreeModel(&md2file);
    delete myTex;
}

int _3DModelLoader::ReadMD2Model(const char* filename, struct md2_model_t* mdl)
{
    FILE *fp;
    fp = fopen (filename, "rb");
    if (!fp) { /* ... error ... */ return 0; }

    fread (&mdl->header, 1, sizeof (struct md2_header_t), fp);
    if ((mdl->header.ident != 844121161) || (mdl->header.version != 8)) {
        /* ... error ... */ fclose (fp); return 0;
    }

    /* Memory allocations (no change) */
    mdl->skins = (struct md2_skin_t *)malloc (sizeof (struct md2_skin_t) * mdl->header.num_skins);
    mdl->texcoords = (struct md2_texCoord_t *)malloc (sizeof (struct md2_texCoord_t) * mdl->header.num_st);
    mdl->triangles = (struct md2_triangle_t *)malloc (sizeof (struct md2_triangle_t) * mdl->header.num_tris);
    mdl->frames = (struct md2_frame_t *)malloc (sizeof (struct md2_frame_t) * mdl->header.num_frames);
    mdl->glcmds = (int *)malloc (sizeof (int) * mdl->header.num_glcmds);

    /* Read model data (no change) */
    fseek (fp, mdl->header.offset_skins, SEEK_SET);
    fread (mdl->skins, sizeof (struct md2_skin_t),mdl->header.num_skins, fp);
    fseek (fp, mdl->header.offset_st, SEEK_SET);
    fread (mdl->texcoords, sizeof (struct md2_texCoord_t),mdl->header.num_st, fp);
    fseek (fp, mdl->header.offset_tris, SEEK_SET);
    fread (mdl->triangles, sizeof (struct md2_triangle_t),mdl->header.num_tris, fp);
    fseek (fp, mdl->header.offset_glcmds, SEEK_SET);
    fread (mdl->glcmds, sizeof (int), mdl->header.num_glcmds, fp);

    /* Read frames */
    std::cout << "--- Parsing MD2 Animations ---" << std::endl;
    int standMin = 999, standMax = 0;
    int runMin = 999, runMax = 0;

    fseek (fp, mdl->header.offset_frames, SEEK_SET);
    for (int i = 0; i < mdl->header.num_frames; ++i)
    {
        mdl->frames[i].verts = (struct md2_vertex_t *)malloc (sizeof (struct md2_vertex_t) * mdl->header.num_vertices);

        // CHANGED: Use sizeof(vec3) and pass address of struct
        fread (&mdl->frames[i].scale, sizeof (vec3), 1, fp);
        fread (&mdl->frames[i].translate, sizeof (vec3), 1, fp);

        fread (mdl->frames[i].name, sizeof (char), 16, fp);
        fread (mdl->frames[i].verts, sizeof (struct md2_vertex_t),mdl->header.num_vertices, fp);

        std::string frameName(mdl->frames[i].name);

        if (frameName.rfind("stand", 0) == 0) {
            standMin = std::min(standMin, i);
            standMax = std::max(standMax, i);
        }
        if (frameName.rfind("run", 0) == 0) {
            runMin = std::min(runMin, i);
            runMax = std::max(runMax, i);
        }
    }
    // ... (rest of parsing logic is the same) ...
    if (standMin < 999) {
        animStandStart = standMin;
        animStandEnd = standMax;
        std::cout << "Found 'stand' animation: " << animStandStart << " - " << animStandEnd << std::endl;
    }
    if (runMin < 999) {
        animWalkStart = runMin;
        animWalkEnd = runMax;
        std::cout << "Found 'walk' (run) animation: " << animWalkStart << " - " << animWalkEnd << std::endl;
    }
    setAnimation(animStandStart, animStandEnd);

    /* Texture Loading (no change) */
    if (mdl->header.num_skins > 0)
    {
        const char* texturePath = "models/Tekk/blade.jpg";
        if (myTex->loadTexture(texturePath)) {
            mdl->tex_id = myTex->getID();
        } else {
            std::cout << "Error: Failed to load texture " << texturePath << std::endl;
        }
    }

    fclose (fp);
    return 1;
}

void _3DModelLoader::setAnimation(int start, int end)
{
    if (currentAnimStart == start) { return; }
    currentAnimStart = start;
    currentAnimEnd = end;
    currentFrame = start;
    interp = 0.0f;
}

void _3DModelLoader::stand() { setAnimation(animStandStart, animStandEnd); }
void _3DModelLoader::walk() { setAnimation(animWalkStart, animWalkEnd); }

void _3DModelLoader::translate(double dx, double dy, double dz)
{
    pos.x += dx;
    pos.y += dy;
    pos.z += dz;
}

void _3DModelLoader::update(float dt)
{
    interp += 10.0f * dt;
    Animate(currentAnimStart, currentAnimEnd, &currentFrame, &interp);
}

void _3DModelLoader::Draw()
{
    glPushMatrix();
        glTranslatef (pos.x, pos.y, pos.z);
        glRotatef(rotateX, 1.0, 0.0, 0.0);
        glRotatef(rotateY, 0.0, 1.0, 0.0);
        glRotatef(rotateZ, 0.0, 0.0, 1.0);
        glScalef(scale, scale, scale);
        glRotatef (-90.0f, 1.0, 0.0, 0.0);
        glRotatef (-90.0f, 0.0, 0.0, 1.0);
        RenderFrameItpWithGLCmds (currentFrame, interp, &md2file);
    glPopMatrix();
}


void _3DModelLoader::RenderFrameItpWithGLCmds(int n, float interp, const struct md2_model_t* mdl)
{
    // --- Local variables CHANGED ---
    int i, *pglcmds;
    vec3 v_curr, v_next, v, norm; // <-- CHANGED from vec3_t
    struct md2_frame_t *pframe1, *pframe2;
    struct md2_vertex_t *pvert1, *pvert2;
    struct md2_glcmd_t *packet;

    if ((n < 0) || (n > mdl->header.num_frames - 1)) return;

    glBindTexture (GL_TEXTURE_2D, mdl->tex_id);
    pglcmds = mdl->glcmds;

    while ((i = *(pglcmds++)) != 0) {
        if (i < 0) {
            glBegin (GL_TRIANGLE_FAN);
            i = -i;
        } else {
            glBegin (GL_TRIANGLE_STRIP);
        }

        for (/* Nothing */; i > 0; --i, pglcmds += 3) {
            packet = (struct md2_glcmd_t *)pglcmds;
            pframe1 = &mdl->frames[n];
            int nextFrame = n + 1;

            // 2. Check if the next frame is OUTSIDE the current animation
            if (nextFrame > this->currentAnimEnd)
            {
                // 3. If it is, wrap back to the START of this animation
                nextFrame = this->currentAnimStart;
            }
            pframe2 = &mdl->frames[nextFrame];

            pvert1 = &pframe1->verts[packet->index];
            pvert2 = &pframe2->verts[packet->index];
            glTexCoord2f (packet->s, packet->t);

            // --- CHANGED: Use .x, .y, .z and const ref ---
            const vec3& n_curr = anorms_table[pvert1->normalIndex];
            const vec3& n_next = anorms_table[pvert2->normalIndex];

            norm.x = n_curr.x + interp * (n_next.x - n_curr.x);
            norm.y = n_curr.y + interp * (n_next.y - n_curr.y);
            norm.z = n_curr.z + interp * (n_next.z - n_curr.z);
            glNormal3f (norm.x, norm.y, norm.z); // <-- CHANGED

            v_curr.x = pframe1->scale.x * pvert1->v[0] + pframe1->translate.x;
            v_curr.y = pframe1->scale.y * pvert1->v[1] + pframe1->translate.y;
            v_curr.z = pframe1->scale.z * pvert1->v[2] + pframe1->translate.z;

            v_next.x = pframe2->scale.x * pvert2->v[0] + pframe2->translate.x;
            v_next.y = pframe2->scale.y * pvert2->v[1] + pframe2->translate.y;
            v_next.z = pframe2->scale.z * pvert2->v[2] + pframe2->translate.z;

            v.x = v_curr.x + interp * (v_next.x - v_curr.x);
            v.y = v_curr.y + interp * (v_next.y - v_curr.y);
            v.z = v_curr.z + interp * (v_next.z - v_curr.z);
            glVertex3f (v.x, v.y, v.z); // <-- CHANGED
        }
        glEnd ();
    }
}

void _3DModelLoader::Animate(int start, int end, int* frame, float* interp)
{
    if (*interp >= 1.0f)
    {
        *interp = 0.0f;
        (*frame)++;
        if (*frame > end)
            *frame = start;
    }
}

void _3DModelLoader::initModel(const char* filename)
{
    if (!ReadMD2Model (filename, &md2file))
        exit (EXIT_FAILURE);
}

void _3DModelLoader::FreeModel(struct md2_model_t* mdl)
{
    if (mdl->skins) { free (mdl->skins); mdl->skins = NULL; }
    if (mdl->texcoords) { free (mdl->texcoords); mdl->texcoords = NULL; }
    if (mdl->triangles) { free (mdl->triangles); mdl->triangles = NULL; }
    if (mdl->glcmds) { free (mdl->glcmds); mdl->glcmds = NULL; }
    if (mdl->frames) {
        for (int i = 0; i < mdl->header.num_frames; ++i) {
            if (mdl->frames[i].verts) {
                free (mdl->frames[i].verts);
                mdl->frames[i].verts = NULL;
            }
        }
        free (mdl->frames);
        mdl->frames = NULL;
    }
}
