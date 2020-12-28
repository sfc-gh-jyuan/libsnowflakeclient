/*
 * Copyright (c) 2020 Snowflake Computing, Inc. All rights reserved.
 */

#include <string>

#include "memory.h"
#include "snowflake/result_set_arrow.h"


result_set_arrow_t * result_set_arrow_create(
    cJSON * data,
    SF_COLUMN_DESC * metadata,
    SF_CHUNK_DOWNLOADER * chunk_downloader,
    char * query_id,
    int32 tz_offset,
    int64 total_chunk_count,
    int64 total_column_count,
    int64 total_row_count
)
{
    result_set_arrow_t * rs_struct;
    rs_struct = (typeof(rs_struct)) SF_MALLOC(sizeof(*rs_struct));
    Snowflake::Client::ResultSetArrow * rs_obj =
        new Snowflake::Client::ResultSetArrow(
            data,
            metadata,
            chunk_downloader,
            std::string(query_id),
            tz_offset,
            total_chunk_count,
            total_column_count,
            total_row_count);
    rs_struct->result_set_object = rs_obj;

    return rs_struct;
}

void result_set_arrow_destroy(result_set_arrow_t * rs)
{
    if (rs == NULL)
    {
        return;
    }

    delete static_cast<Snowflake::Client::ResultSetArrow *>(rs->result_set_object);
    SF_FREE(rs);
}

bool result_set_arrow_next_column(result_set_arrow_t * rs)
{
    Snowflake::Client::ResultSetArrow * rs_obj;

    if (rs == NULL)
    {
        return false;
    }

    rs_obj = static_cast<Snowflake::Client::ResultSetArrow *> (rs->result_set_object);
    return rs_obj->nextColumn();
}

bool result_set_arrow_next_row(result_set_arrow_t * rs)
{
    Snowflake::Client::ResultSetArrow * rs_obj;

    if (rs == NULL)
    {
        return false;
    }

    rs_obj = static_cast<Snowflake::Client::ResultSetArrow *> (rs->result_set_object);
    return rs_obj->nextRow();
}

std::string result_set_arrow_get_current_column(result_set_arrow_t * rs)
{
    Snowflake::Client::ResultSetArrow * rs_obj;

    if (rs == NULL)
    {
        return NULL;
    }

    rs_obj = static_cast<Snowflake::Client::ResultSetArrow *> (rs->result_set_object);
    return rs_obj->getCurrentColumnAsString();
}

std::string result_set_arrow_get_current_row(result_set_arrow_t * rs)
{
    Snowflake::Client::ResultSetArrow * rs_obj;

    if (rs == NULL)
    {
        return NULL;
    }

    rs_obj = static_cast<Snowflake::Client::ResultSetArrow *> (rs->result_set_object);
    return rs_obj->getCurrentRowAsString();
}