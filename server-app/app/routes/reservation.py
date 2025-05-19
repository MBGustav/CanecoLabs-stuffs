from fastapi import APIRouter, Depends, HTTPException
from starlette.responses import RedirectResponse
from sqlmodel import Field, Session, SQLModel, create_engine, select, Relationship
from db.db_handler import get_session
from models.models import *
from routes.access_history import access_log
from datetime import timedelta


"""
Definimos que o sistema terá um sistema de reserva em blocos de 30 min.
Dessa forma, temos as seguintes regras de negocio:
- blocos de 30min,
- intervalos de horario de 24hrs.
- O Estudante(Monitor) tem o direito de reservar apenas 1 vez ao dia
- O Presidente tem o direito de reservar ilimitado 
- O Presidente pode alterar reservas
- O Presidente pode remover reservas
- O Estudante pode somente consultar a reserva
- O Monitor nao pode remover reservas
- Todos podem consultar as reservas

"""

router = APIRouter()


@router.get("/reserve")
def read_reserve(reserve :ReservationQuery, session :Session  = Depends(get_session)):
    try: 
        date_beg = datetime.now()
        if reserve.date_stamp is not None:
            date_beg = reserve.date_stamp

        date_end = date_beg + timedelta(hours=5)
        
        query = select(ReserveHistory)
        query = query.where(ReserveHistory.date_stamp >= date_beg,
                            ReserveHistory.date_stamp <= date_end)
        query = query.order_by(ReserveHistory.date_stamp).limit(10)
        result = session.exec(query).all()
        return result


    except Exception as e:
        raise HTTPException(status_code=400, detail=f":\n {str(e)}")

@router.post("/reserve")
def read_reserve(reserve :ReservationQuery, session :Session  = Depends(get_session)):
    raise HTTPException(status_code=501, detail=f"Not Implemented:\n")
