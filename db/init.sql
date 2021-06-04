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

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: block; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.block (
                              id integer NOT NULL,
                              "teacherId" integer NOT NULL,
                              "subjectId" integer NOT NULL,
                              "groupId" integer NOT NULL
);


ALTER TABLE public.block OWNER TO postgres;

--
-- Name: block_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.block_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.block_id_seq OWNER TO postgres;

--
-- Name: block_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.block_id_seq OWNED BY public.block.id;


--
-- Name: classroom; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.classroom (
                                  id integer NOT NULL,
                                  "classroomName" text NOT NULL,
                                  "classroomType" integer DEFAULT 0 NOT NULL
);


ALTER TABLE public.classroom OWNER TO postgres;

--
-- Name: classroom_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.classroom_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.classroom_id_seq OWNER TO postgres;

--
-- Name: classroom_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.classroom_id_seq OWNED BY public.classroom.id;


--
-- Name: studygroup; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.studygroup (
                                   id integer NOT NULL,
                                   "groupName" text NOT NULL
);


ALTER TABLE public.studygroup OWNER TO postgres;

--
-- Name: studyGroup_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."studyGroup_id_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."studyGroup_id_seq" OWNER TO postgres;

--
-- Name: studyGroup_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."studyGroup_id_seq" OWNED BY public.studygroup.id;


--
-- Name: subject; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.subject (
                                id integer NOT NULL,
                                "subjectName" text NOT NULL,
                                "subjectType" integer DEFAULT 0 NOT NULL
);


ALTER TABLE public.subject OWNER TO postgres;

--
-- Name: subject_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.subject_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.subject_id_seq OWNER TO postgres;

--
-- Name: subject_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.subject_id_seq OWNED BY public.subject.id;


--
-- Name: teacher; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.teacher (
                                id integer NOT NULL,
                                "teacherName" text NOT NULL
);


ALTER TABLE public.teacher OWNER TO postgres;

--
-- Name: teacher_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.teacher_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.teacher_id_seq OWNER TO postgres;

--
-- Name: teacher_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.teacher_id_seq OWNED BY public.teacher.id;


--
-- Name: timeslot; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.timeslot (
                                 id integer NOT NULL,
                                 "timeSlotName" text NOT NULL
);


ALTER TABLE public.timeslot OWNER TO postgres;

--
-- Name: timeSlot_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."timeSlot_id_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."timeSlot_id_seq" OWNER TO postgres;

--
-- Name: timeSlot_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."timeSlot_id_seq" OWNED BY public.timeslot.id;


--
-- Name: timetable; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.timetable (
                                  id integer NOT NULL,
                                  "classroomId" integer NOT NULL,
                                  "timeId" integer NOT NULL,
                                  "blockId" integer NOT NULL
);


ALTER TABLE public.timetable OWNER TO postgres;

--
-- Name: timetable_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.timetable_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.timetable_id_seq OWNER TO postgres;

--
-- Name: timetable_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.timetable_id_seq OWNED BY public.timetable.id;


--
-- Name: block id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.block ALTER COLUMN id SET DEFAULT nextval('public.block_id_seq'::regclass);


--
-- Name: classroom id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.classroom ALTER COLUMN id SET DEFAULT nextval('public.classroom_id_seq'::regclass);


--
-- Name: studygroup id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.studygroup ALTER COLUMN id SET DEFAULT nextval('public."studyGroup_id_seq"'::regclass);


--
-- Name: subject id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.subject ALTER COLUMN id SET DEFAULT nextval('public.subject_id_seq'::regclass);


--
-- Name: teacher id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.teacher ALTER COLUMN id SET DEFAULT nextval('public.teacher_id_seq'::regclass);


--
-- Name: timeslot id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.timeslot ALTER COLUMN id SET DEFAULT nextval('public."timeSlot_id_seq"'::regclass);


--
-- Name: timetable id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.timetable ALTER COLUMN id SET DEFAULT nextval('public.timetable_id_seq'::regclass);


--
-- Name: block block_pk; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.block
    ADD CONSTRAINT block_pk PRIMARY KEY (id);


--
-- Name: classroom classroom_pk; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.classroom
    ADD CONSTRAINT classroom_pk PRIMARY KEY (id);


--
-- Name: studygroup studygroup_pk; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.studygroup
    ADD CONSTRAINT studygroup_pk PRIMARY KEY (id);


--
-- Name: subject subject_pk; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.subject
    ADD CONSTRAINT subject_pk PRIMARY KEY (id);


--
-- Name: teacher teacher_pk; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.teacher
    ADD CONSTRAINT teacher_pk PRIMARY KEY (id);


--
-- Name: timeslot timeslot_pk; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.timeslot
    ADD CONSTRAINT timeslot_pk PRIMARY KEY (id);


--
-- Name: timetable timetable_pk; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.timetable
    ADD CONSTRAINT timetable_pk PRIMARY KEY (id);


--
-- Name: block_subjectid_groupid_uindex; Type: INDEX; Schema: public; Owner: postgres
--

CREATE UNIQUE INDEX block_subjectid_groupid_uindex ON public.block USING btree ("subjectId", "groupId");


--
-- Name: classroom_classroomname_uindex; Type: INDEX; Schema: public; Owner: postgres
--

CREATE UNIQUE INDEX classroom_classroomname_uindex ON public.classroom USING btree ("classroomName");


--
-- Name: studygroup_groupname_uindex; Type: INDEX; Schema: public; Owner: postgres
--

CREATE UNIQUE INDEX studygroup_groupname_uindex ON public.studygroup USING btree ("groupName");


--
-- Name: subject_subjectname_subjecttype_uindex; Type: INDEX; Schema: public; Owner: postgres
--

CREATE UNIQUE INDEX subject_subjectname_subjecttype_uindex ON public.subject USING btree ("subjectName", "subjectType");


--
-- Name: timeslot_timeslotname_uindex; Type: INDEX; Schema: public; Owner: postgres
--

CREATE UNIQUE INDEX timeslot_timeslotname_uindex ON public.timeslot USING btree ("timeSlotName");


--
-- Name: timetable_classroomid_timeid_blockid_uindex; Type: INDEX; Schema: public; Owner: postgres
--

CREATE UNIQUE INDEX timetable_classroomid_timeid_blockid_uindex ON public.timetable USING btree ("classroomId", "timeId", "blockId");


--
-- Name: block block_studygroup_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.block
    ADD CONSTRAINT block_studygroup_id_fk FOREIGN KEY ("groupId") REFERENCES public.studygroup(id);


--
-- Name: block block_subject_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.block
    ADD CONSTRAINT block_subject_id_fk FOREIGN KEY ("subjectId") REFERENCES public.subject(id);


--
-- Name: block block_teacher_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.block
    ADD CONSTRAINT block_teacher_id_fk FOREIGN KEY ("teacherId") REFERENCES public.teacher(id);


--
-- Name: timetable timetable_block_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.timetable
    ADD CONSTRAINT timetable_block_id_fk FOREIGN KEY ("blockId") REFERENCES public.block(id);


--
-- Name: timetable timetable_classroom_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.timetable
    ADD CONSTRAINT timetable_classroom_id_fk FOREIGN KEY ("classroomId") REFERENCES public.classroom(id);


--
-- Name: timetable timetable_timeslot_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.timetable
    ADD CONSTRAINT timetable_timeslot_id_fk FOREIGN KEY ("timeId") REFERENCES public.timeslot(id);


--
-- PostgreSQL database dump complete
--

