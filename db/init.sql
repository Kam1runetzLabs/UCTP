DROP DATABASE IF EXISTS schedules;
CREATE DATABASE schedules;
\c schedules

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: content; Type: SCHEMA; Schema: -; Owner: postgres
--
CREATE SCHEMA IF NOT EXISTS content;
ALTER SCHEMA content OWNER TO postgres;
SET search_path TO content, public;

BEGIN;

--
-- Name: campus_name; Type: TYPE; Schema: content; Owner: postgres
--
CREATE TYPE content.campus_name AS ENUM (
    'GZ',
    'ULK',
    'SM',
    'E',
    'MT',
    'SK',
    'Orevo'
);
ALTER TYPE content.campus_name OWNER TO postgres;

--
-- Name: day_of_week; Type: TYPE; Schema: content; Owner: postgres
--
CREATE TYPE content.day_of_week AS ENUM (
    'monday',
    'tuesday',
    'wednesday',
    'thursday',
    'friday',
    'saturday',
    'sunday'
);
ALTER TYPE content.day_of_week OWNER TO postgres;

--
-- Name: lesson_week; Type: TYPE; Schema: content; Owner: postgres
--
CREATE TYPE content.lesson_week AS ENUM (
    'odd',
    'even',
    'both'
);
ALTER TYPE content.lesson_week OWNER TO postgres;

--
-- Name: subject_type; Type: TYPE; Schema: content; Owner: postgres
--
CREATE TYPE content.subject_type AS ENUM (
    'lecture',
    'seminar',
    'lab',
    'pe'
);
ALTER TYPE content.subject_type OWNER TO postgres;

SET default_tablespace = '';
SET default_table_access_method = heap;

--
-- Name: academic_plan; Type: TABLE; Schema: content; Owner: postgres
--
CREATE TABLE content.academic_plan (
                                       uuid uuid NOT NULL,
                                       speciality_id uuid NOT NULL,
                                       department_id uuid NOT NULL,
                                       subject_id uuid NOT NULL,
                                       lessons_number smallint DEFAULT 1 NOT NULL,
                                       semester smallint DEFAULT 1 NOT NULL
);
ALTER TABLE content.academic_plan OWNER TO postgres;

--
-- Name: academic_plan_classroom; Type: TABLE; Schema: content; Owner: postgres
--
CREATE TABLE content.academic_plan_classroom (
                                                 uuid uuid NOT NULL,
                                                 academic_plan_id uuid NOT NULL,
                                                 classroom_id uuid NOT NULL
);
ALTER TABLE content.academic_plan_classroom OWNER TO postgres;

--
-- Name: academic_plan_group; Type: TABLE; Schema: content; Owner: postgres
--
CREATE TABLE content.academic_plan_group (
                                             uuid uuid NOT NULL,
                                             academic_plan_id uuid NOT NULL,
                                             group_id uuid NOT NULL
);
ALTER TABLE content.academic_plan_group OWNER TO postgres;

--
-- Name: academic_plan_teacher; Type: TABLE; Schema: content; Owner: postgres
--
CREATE TABLE content.academic_plan_teacher (
                                               uuid uuid NOT NULL,
                                               academic_plan_id uuid NOT NULL,
                                               teacher_id uuid NOT NULL
);
ALTER TABLE content.academic_plan_teacher OWNER TO postgres;

--
-- Name: classroom; Type: TABLE; Schema: content; Owner: postgres
--
CREATE TABLE content.classroom (
                                   uuid uuid NOT NULL,
                                   campus content.campus_name DEFAULT 'GZ'::content.campus_name NOT NULL,
                                   for_lectures boolean DEFAULT false NOT NULL,
                                   for_seminars boolean DEFAULT false NOT NULL,
                                   for_lab boolean DEFAULT false NOT NULL,
                                   for_pe boolean DEFAULT false NOT NULL,
                                   number character varying(10) NOT NULL,
                                   capacity smallint DEFAULT 1 NOT NULL
);
ALTER TABLE content.classroom OWNER TO postgres;

--
-- Name: classroom_lesson; Type: TABLE; Schema: content; Owner: postgres
--
CREATE TABLE content.classroom_lesson (
                                          uuid uuid NOT NULL,
                                          classroom_id uuid NOT NULL,
                                          lesson_id uuid NOT NULL
);
ALTER TABLE content.classroom_lesson OWNER TO postgres;

--
-- Name: department; Type: TABLE; Schema: content; Owner: postgres
--
CREATE TABLE content.department (
                                    uuid uuid NOT NULL,
                                    name character varying(100) NOT NULL,
                                    code character varying(20) NOT NULL
);
ALTER TABLE content.department OWNER TO postgres;

--
-- Name: group; Type: TABLE; Schema: content; Owner: postgres
--
CREATE TABLE content."group" (
                                 uuid uuid NOT NULL,
                                 code character varying(20) NOT NULL,
                                 students_number smallint DEFAULT 1 NOT NULL,
                                 admission_year smallint DEFAULT 2015 NOT NULL
);
ALTER TABLE content."group" OWNER TO postgres;

--
-- Name: lesson; Type: TABLE; Schema: content; Owner: postgres
--
CREATE TABLE content.lesson (
                                uuid uuid NOT NULL,
                                subject_id uuid NOT NULL,
                                group_id uuid NOT NULL,
                                lesson_number smallint NOT NULL,
                                day_of_week content.day_of_week NOT NULL,
                                lesson_week content.lesson_week NOT NULL,
                                is_remote boolean NOT NULL,
                                schedule_id uuid NOT NULL
);
ALTER TABLE content.lesson OWNER TO postgres;

--
-- Name: schedule; Type: TABLE; Schema: content; Owner: postgres
--
CREATE TABLE content.schedule (
                                  uuid uuid NOT NULL,
                                  created timestamp with time zone NOT NULL,
                                  is_deprecated boolean DEFAULT false NOT NULL
);
ALTER TABLE content.schedule OWNER TO postgres;

--
-- Name: speciality; Type: TABLE; Schema: content; Owner: postgres
--
CREATE TABLE content.speciality (
                                    uuid uuid NOT NULL,
                                    name character varying(100) NOT NULL,
                                    code character varying(20) NOT NULL
);
ALTER TABLE content.speciality OWNER TO postgres;

--
-- Name: subject; Type: TABLE; Schema: content; Owner: postgres
--
CREATE TABLE content.subject (
                                 uuid uuid NOT NULL,
                                 name character varying(100) NOT NULL,
                                 type content.subject_type DEFAULT 'seminar'::content.subject_type NOT NULL,
                                 teachers_number smallint DEFAULT 1 NOT NULL,
                                 classrooms_number smallint DEFAULT 1 NOT NULL,
                                 remote_available boolean DEFAULT true NOT NULL
);
ALTER TABLE content.subject OWNER TO postgres;

--
-- Name: teacher; Type: TABLE; Schema: content; Owner: postgres
--
CREATE TABLE content.teacher (
                                 uuid uuid NOT NULL,
                                 first_name character varying(100) NOT NULL,
                                 second_name character varying(100),
                                 last_name character varying(100) NOT NULL,
                                 unavailable_time json,
                                 remote_availability json
);
ALTER TABLE content.teacher OWNER TO postgres;

--
-- Name: teacher_lesson; Type: TABLE; Schema: content; Owner: postgres
--
CREATE TABLE content.teacher_lesson (
                                        uuid uuid NOT NULL,
                                        teacher_id uuid NOT NULL,
                                        lesson_id uuid NOT NULL
);
ALTER TABLE content.teacher_lesson OWNER TO postgres;


-- insert values


-- create constraints and indices
--
-- Name: academic_plan_classroom academic_plan_classroom_pk; Type: CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.academic_plan_classroom
    ADD CONSTRAINT academic_plan_classroom_pk PRIMARY KEY (uuid);

--
-- Name: academic_plan_group academic_plan_group_pk; Type: CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.academic_plan_group
    ADD CONSTRAINT academic_plan_group_pk PRIMARY KEY (uuid);

--
-- Name: academic_plan academic_plan_pk; Type: CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.academic_plan
    ADD CONSTRAINT academic_plan_pk PRIMARY KEY (uuid);

--
-- Name: academic_plan_teacher academic_plan_teacher_pk; Type: CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.academic_plan_teacher
    ADD CONSTRAINT academic_plan_teacher_pk PRIMARY KEY (uuid);

--
-- Name: classroom_lesson classroom_lesson_pk; Type: CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.classroom_lesson
    ADD CONSTRAINT classroom_lesson_pk PRIMARY KEY (uuid);

--
-- Name: classroom classroom_pk; Type: CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.classroom
    ADD CONSTRAINT classroom_pk PRIMARY KEY (uuid);

--
-- Name: department department_pk; Type: CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.department
    ADD CONSTRAINT department_pk PRIMARY KEY (uuid);

--
-- Name: group group_pk; Type: CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content."group"
    ADD CONSTRAINT group_pk PRIMARY KEY (uuid);

--
-- Name: lesson lesson_pk; Type: CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.lesson
    ADD CONSTRAINT lesson_pk PRIMARY KEY (uuid);

--
-- Name: schedule schedule_pk; Type: CONSTRAINT; Schema: content; Owner: postgres
--

ALTER TABLE ONLY content.schedule
    ADD CONSTRAINT schedule_pk PRIMARY KEY (uuid);

--
-- Name: speciality speciality_pk; Type: CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.speciality
    ADD CONSTRAINT speciality_pk PRIMARY KEY (uuid);

--
-- Name: subject subject_pk; Type: CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.subject
    ADD CONSTRAINT subject_pk PRIMARY KEY (uuid);

--
-- Name: teacher_lesson teacher_lesson_pk; Type: CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.teacher_lesson
    ADD CONSTRAINT teacher_lesson_pk PRIMARY KEY (uuid);

--
-- Name: teacher teacher_pk; Type: CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.teacher
    ADD CONSTRAINT teacher_pk PRIMARY KEY (uuid);

--
-- Name: academic_plan_classroom_academic_plan_id_classroom_id_uindex; Type: INDEX; Schema: content; Owner: postgres
--
CREATE UNIQUE INDEX academic_plan_classroom_academic_plan_id_classroom_id_uindex ON content.academic_plan_classroom USING btree (academic_plan_id, classroom_id);

--
-- Name: academic_plan_group_academic_plan_id_group_id_uindex; Type: INDEX; Schema: content; Owner: postgres
--
CREATE UNIQUE INDEX academic_plan_group_academic_plan_id_group_id_uindex ON content.academic_plan_group USING btree (academic_plan_id, group_id);

--
-- Name: academic_plan_speciality_id_department_id_subject_id_semester_u; Type: INDEX; Schema: content; Owner: postgres
--
CREATE UNIQUE INDEX academic_plan_speciality_id_department_id_subject_id_semester_u ON content.academic_plan USING btree (speciality_id, department_id, subject_id, semester);

--
-- Name: academic_plan_teacher_academic_plan_id_teacher_id_uindex; Type: INDEX; Schema: content; Owner: postgres
--
CREATE UNIQUE INDEX academic_plan_teacher_academic_plan_id_teacher_id_uindex ON content.academic_plan_teacher USING btree (academic_plan_id, teacher_id);

--
-- Name: classroom_campus_number_uindex; Type: INDEX; Schema: content; Owner: postgres
--
CREATE UNIQUE INDEX classroom_campus_number_uindex ON content.classroom USING btree (campus, number);

--
-- Name: classroom_lesson_classroom_id_lesson_id_uindex; Type: INDEX; Schema: content; Owner: postgres
--
CREATE UNIQUE INDEX classroom_lesson_classroom_id_lesson_id_uindex ON content.classroom_lesson USING btree (classroom_id, lesson_id);

--
-- Name: department_code_uindex; Type: INDEX; Schema: content; Owner: postgres
--
CREATE UNIQUE INDEX department_code_uindex ON content.department USING btree (code);

--
-- Name: group_code_uindex; Type: INDEX; Schema: content; Owner: postgres
--
CREATE UNIQUE INDEX group_code_uindex ON content."group" USING btree (code);

--
-- Name: lesson_group_id_lesson_number_day_of_week_schedule_id_uindex; Type: INDEX; Schema: content; Owner: postgres
--
CREATE UNIQUE INDEX lesson_group_id_lesson_number_day_of_week_schedule_id_uindex ON content.lesson USING btree (group_id, lesson_number, day_of_week, schedule_id);

--
-- Name: speciality_code_uindex; Type: INDEX; Schema: content; Owner: postgres
--
CREATE UNIQUE INDEX speciality_code_uindex ON content.speciality USING btree (code);

--
-- Name: subject_name_type_uindex; Type: INDEX; Schema: content; Owner: postgres
--
CREATE UNIQUE INDEX subject_name_type_uindex ON content.subject USING btree (name, type);

--
-- Name: teacher_lesson_teacher_id_lesson_id_uindex; Type: INDEX; Schema: content; Owner: postgres
--
CREATE UNIQUE INDEX teacher_lesson_teacher_id_lesson_id_uindex ON content.teacher_lesson USING btree (teacher_id, lesson_id);

--
-- Name: academic_plan_classroom academic_plan_classroom_academic_plan_uuid_fk; Type: FK CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.academic_plan_classroom
    ADD CONSTRAINT academic_plan_classroom_academic_plan_uuid_fk FOREIGN KEY (academic_plan_id) REFERENCES content.academic_plan(uuid) ON UPDATE RESTRICT ON DELETE RESTRICT;

--
-- Name: academic_plan_classroom academic_plan_classroom_classroom_uuid_fk; Type: FK CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.academic_plan_classroom
    ADD CONSTRAINT academic_plan_classroom_classroom_uuid_fk FOREIGN KEY (classroom_id) REFERENCES content.classroom(uuid) ON UPDATE RESTRICT ON DELETE RESTRICT;

--
-- Name: academic_plan academic_plan_department_uuid_fk; Type: FK CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.academic_plan
    ADD CONSTRAINT academic_plan_department_uuid_fk FOREIGN KEY (department_id) REFERENCES content.department(uuid) ON UPDATE RESTRICT ON DELETE RESTRICT;

--
-- Name: academic_plan_group academic_plan_group_academic_plan_uuid_fk; Type: FK CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.academic_plan_group
    ADD CONSTRAINT academic_plan_group_academic_plan_uuid_fk FOREIGN KEY (academic_plan_id) REFERENCES content.academic_plan(uuid) ON UPDATE RESTRICT ON DELETE RESTRICT;

--
-- Name: academic_plan_group academic_plan_group_group_uuid_fk; Type: FK CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.academic_plan_group
    ADD CONSTRAINT academic_plan_group_group_uuid_fk FOREIGN KEY (group_id) REFERENCES content."group"(uuid) ON UPDATE RESTRICT ON DELETE RESTRICT;

--
-- Name: academic_plan academic_plan_speciality_uuid_fk; Type: FK CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.academic_plan
    ADD CONSTRAINT academic_plan_speciality_uuid_fk FOREIGN KEY (speciality_id) REFERENCES content.speciality(uuid) ON UPDATE RESTRICT ON DELETE RESTRICT;

--
-- Name: academic_plan academic_plan_subject_uuid_fk; Type: FK CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.academic_plan
    ADD CONSTRAINT academic_plan_subject_uuid_fk FOREIGN KEY (subject_id) REFERENCES content.subject(uuid) ON UPDATE RESTRICT ON DELETE RESTRICT;

--
-- Name: academic_plan_teacher academic_plan_teacher_academic_plan_uuid_fk; Type: FK CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.academic_plan_teacher
    ADD CONSTRAINT academic_plan_teacher_academic_plan_uuid_fk FOREIGN KEY (academic_plan_id) REFERENCES content.academic_plan(uuid) ON UPDATE RESTRICT ON DELETE RESTRICT;

--
-- Name: academic_plan_teacher academic_plan_teacher_teacher_uuid_fk; Type: FK CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.academic_plan_teacher
    ADD CONSTRAINT academic_plan_teacher_teacher_uuid_fk FOREIGN KEY (teacher_id) REFERENCES content.teacher(uuid) ON UPDATE RESTRICT ON DELETE RESTRICT;

--
-- Name: classroom_lesson classroom_lesson_classroom_uuid_fk; Type: FK CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.classroom_lesson
    ADD CONSTRAINT classroom_lesson_classroom_uuid_fk FOREIGN KEY (classroom_id) REFERENCES content.classroom(uuid) ON UPDATE RESTRICT ON DELETE RESTRICT;

--
-- Name: classroom_lesson classroom_lesson_lesson_uuid_fk; Type: FK CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.classroom_lesson
    ADD CONSTRAINT classroom_lesson_lesson_uuid_fk FOREIGN KEY (lesson_id) REFERENCES content.lesson(uuid) ON UPDATE RESTRICT ON DELETE RESTRICT;

--
-- Name: lesson lesson_group_uuid_fk; Type: FK CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.lesson
    ADD CONSTRAINT lesson_group_uuid_fk FOREIGN KEY (group_id) REFERENCES content."group"(uuid) ON UPDATE RESTRICT ON DELETE RESTRICT;

--
-- Name: lesson lesson_schedule_uuid_fk; Type: FK CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.lesson
    ADD CONSTRAINT lesson_schedule_uuid_fk FOREIGN KEY (schedule_id) REFERENCES content.schedule(uuid) ON UPDATE RESTRICT ON DELETE RESTRICT;

--
-- Name: lesson lesson_subject_uuid_fk; Type: FK CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.lesson
    ADD CONSTRAINT lesson_subject_uuid_fk FOREIGN KEY (subject_id) REFERENCES content.subject(uuid) ON UPDATE RESTRICT ON DELETE RESTRICT;

--
-- Name: teacher_lesson teacher_lesson_lesson_uuid_fk; Type: FK CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.teacher_lesson
    ADD CONSTRAINT teacher_lesson_lesson_uuid_fk FOREIGN KEY (lesson_id) REFERENCES content.lesson(uuid) ON UPDATE RESTRICT ON DELETE RESTRICT;

--
-- Name: teacher_lesson teacher_lesson_teacher_uuid_fk; Type: FK CONSTRAINT; Schema: content; Owner: postgres
--
ALTER TABLE ONLY content.teacher_lesson
    ADD CONSTRAINT teacher_lesson_teacher_uuid_fk FOREIGN KEY (teacher_id) REFERENCES content.teacher(uuid) ON UPDATE RESTRICT ON DELETE RESTRICT;

COMMIT;
