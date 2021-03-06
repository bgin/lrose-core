C    *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
C    ** Copyright UCAR (c) 1992 - 2010 
C    ** University Corporation for Atmospheric Research(UCAR) 
C    ** National Center for Atmospheric Research(NCAR) 
C    ** Research Applications Laboratory(RAL) 
C    ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA 
C    ** 2010/10/7 23:12:29 
C    *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
C          DATA SET W3FI68     AT LEVEL 005 AS OF 10/12/93
      SUBROUTINE W3FI68 (ID, PDS)
C$$$  SUBPROGRAM DOCUMENTATION BLOCK
C                .      .    .                                       .
C SUBPROGRAM:  W3FI68        CONVERT UP TO 25 WORD ARRAY TO GRIB PDS
C   PRGMMR: FARLEY           ORG: NMC421      DATE:93-10-13
C
C ABSTRACT: CONVERTS AN ARRAY OF 25 INTEGER WORDS INTO A GRIB
C   EDITION 1 PRODUCT DEFINITION SECTION (PDS).  THE LENGTH OF THE
C   PDS IS DETERMINED BY THE VALUE PASSED IN ID(1).
C
C PROGRAM HISTORY LOG:
C   91-05-08  R.E.JONES
C   92-09-25  R.E.JONES   CHANGE TO 25 WORDS OF INPUT, LEVEL
C                         CAN BE IN TWO WORDS. (10,11)
C   93-01-08  R.E.JONES   CHANGE FOR TIME RANGE INDICTOR IF 10,
C                         STORE TIME P1 IN PDS BUTES 19-20.
C   93-01-26  R.E.JONES   CORRECTION FOR FIXED HEIGHT ABOVE
C                         GROUND LEVEL.
C   93-03-29  R.E.JONES   ADD SAVE STATEMENT
C   93-06-24  CAVANAUGH   MODIFIED PROGRAM TO ALLOW FOR GENERATION OF
C                         PDS GREATER THAN 28 BYTES (THE DESIRED PDS
C                         SIZE IS PASSED IN ID(1).
C   93-09-30  FARLEY      CHANGED TO ALLOW FOR SUBCENTER ID; PUT
C                         ID(24) INTO PDS(26).
C   93-10-12  R.E.JONES   CHANGES FOR ON388 REV. OCT 9, 1993, NEW
C                         LEVELS 125, 200, 201.
C
C USAGE:    CALL W3FI68 (ID, PDS)
C   INPUT ARGUMENT LIST:
C     ID       - 25 WORD INTEGER ARRAY
C   OUTPUT ARGUMENT LIST:
C     PDS      - UP TO 50  CHARACTER PDS FOR EDITION 1
C
C REMARKS: LIST CAVEATS, OTHER HELPFUL HINTS OR INFORMATION
C
C ATTRIBUTES:
C   LANGUAGE: CRAY CFT77 FORTRAN 77
C   MACHINE:  CRAY Y-MP8/832
C
C$$$
C
      INTEGER        ID(*)
C
      CHARACTER * 1  PDS(*)
C
      SAVE
C
C     ID(1)  = NUMBER OF BYTES IN PRODUCT DEFINITION SECTION (PDS)
C     ID(2)  = PARAMETER TABLE VERSION NUMBER
C     ID(3)  = IDENTIFICATION OF ORIGINATING CENTER
C     ID(4)  = MODEL IDENTIFICATION (ALLOCATED BY ORIGINATING CENTER)
C     ID(5)  = GRID IDENTIFICATION
C     ID(6)  = 0 IF NO GDS SECTION, 1 IF GDS SECTION IS INCLUDED
C     ID(7)  = 0 IF NO BMS SECTION, 1 IF BMS SECTION IS INCLUDED
C     ID(8)  = INDICATOR OF PARAMETER AND UNITS (TABLE 2)
C     ID(9)  = INDICATOR OF TYPE OF LEVEL       (TABLE 3)
C     ID(10) = VALUE 1 OF LEVEL  (0 FOR 1-100,102,103,105,107
C              109,111,113,125,160,200,201  LEVEL IS IN ID WORD 11)
C     ID(11) = VALUE 2 OF LEVEL
C     ID(12) = YEAR OF CENTURY
C     ID(13) = MONTH OF YEAR
C     ID(14) = DAY OF MONTH
C     ID(15) = HOUR OF DAY
C     ID(16) = MINUTE OF HOUR   (IN MOST CASES SET TO 0)
C     ID(17) = FCST TIME UNIT
C     ID(18) = P1 PERIOD OF TIME
C     ID(19) = P2 PERIOD OF TIME
C     ID(20) = TIME RANGE INDICATOR
C     ID(21) = NUMBER INCLUDED IN AVERAGE
C     ID(22) = NUMBER MISSING FROM AVERAGES
C     ID(23) = CENTURY  (20, CHANGE TO 21 ON JAN. 1, 2001)
C     ID(24) = SUBCENTER IDENTIFICATION
C     ID(25) = SCALING POWER OF 10
C
        PDS(1)  = CHAR(MOD(ID(1)/65536,256))
        PDS(2)  = CHAR(MOD(ID(1)/256,256))
        PDS(3)  = CHAR(MOD(ID(1),256))
        PDS(4)  = CHAR(ID(2))
        PDS(5)  = CHAR(ID(3))
        PDS(6)  = CHAR(ID(4))
        PDS(7)  = CHAR(ID(5))
        PDS(8)  = CHAR(IOR(ISHFT(ID(6),7),
     &                      ISHFT(ID(7),6)))
        PDS(9)  = CHAR(ID(8))
        PDS(10) = CHAR(ID(9))
        I9      = ID(9)
C
C       TEST TYPE OF LEVEL TO SEE IF lEVEL IS IN TWO
C       WORDS OR ONE
C
        IF ((I9.GE.1.AND.I9.LE.100).OR.I9.EQ.102.OR.
     &       I9.EQ.103.OR.I9.EQ.105.OR.I9.EQ.107.OR.
     &       I9.EQ.109.OR.I9.EQ.111.OR.I9.EQ.113.OR.
     &       I9.EQ.125.OR.I9.EQ.160.OR.I9.EQ.200.OR.
     &       I9.EQ.201) THEN
          LEVEL   = ID(11)
          IF (LEVEL.LT.0) THEN
            LEVEL = - LEVEL
            LEVEL = IOR(LEVEL,32768)
          END IF
          PDS(11) = CHAR(MOD(LEVEL/256,256))
          PDS(12) = CHAR(MOD(LEVEL,256))
        ELSE
          PDS(11) = CHAR(ID(10))
          PDS(12) = CHAR(ID(11))
        END IF
        PDS(13) = CHAR(ID(12))
        PDS(14) = CHAR(ID(13))
        PDS(15) = CHAR(ID(14))
        PDS(16) = CHAR(ID(15))
        PDS(17) = CHAR(ID(16))
        PDS(18) = CHAR(ID(17))
C
C       TEST TIME RANGE INDICATOR (PDS BYTE 21) FOR 10
C       IF SO PUT TIME P1 IN PDS BYTES 19-20.
C
        IF (ID(20) .EQ. 10) THEN
          PDS(19) = CHAR(MOD(ID(18)/256,256))
          PDS(20) = CHAR(MOD(ID(18),256))
        ELSE
          PDS(19) = CHAR(ID(18))
          PDS(20) = CHAR(ID(19))
        ENDIF
        PDS(21) = CHAR(ID(20))
        PDS(22) = CHAR(MOD(ID(21)/256,256))
        PDS(23) = CHAR(MOD(ID(21),256))
        PDS(24) = CHAR(ID(22))
        PDS(25) = CHAR(ID(23))
        PDS(26) = CHAR(ID(24))
        ISCALE   = ID(25)
        IF (ISCALE.LT.0) THEN
          ISCALE = -ISCALE
          ISCALE =  IOR(ISCALE,32768)
        END IF
        PDS(27) = CHAR(MOD(ISCALE/256,256))
        PDS(28) = CHAR(MOD(ISCALE    ,256))
        IF (ID(1).GT.28) THEN
            K   = ID(1) - 28
            CALL SBYTES (PDS,0,224,8,0,K)
        END IF
C
      RETURN
      END
